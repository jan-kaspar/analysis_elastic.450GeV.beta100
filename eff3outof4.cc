#include "classes/common_init.hh"
#include "classes/command_line_tools.hh"
#include "classes/common_algorithms.hh"

#include "TFile.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TChain.h"
#include "TH2D.h"
#include "TF1.h"

using namespace std;

// th_x cut
double th_x_min = -200E-6;
double th_x_max = +200E-6;

//----------------------------------------------------------------------------------------------------

struct HistGroup
{
	TH1D *de_th_x, *de_th_y;
	TH1D *th_x;
	TH1D *th_y;
	TH1D *th_y_xcut;
	TH2D *th_x_th_y;
	TH1D *t;

	// map: period --> th_y histogram with th_x cut
	map<signed int, TH1D *> p_th_y_xcut;

	void Init()
	{
		de_th_x = new TH1D("", ";#Delta #theta_{x}", 200, -150E-6, +150E-6);
		de_th_y = new TH1D("", ";#Delta #theta_{y}", 200, -50E-6, +50E-6);

		if (th_x_binning_edges_1d == NULL)
			BuildThBinning();

		th_x = new TH1D("", ";#theta_{x}", th_x_binning_n_1d, th_x_binning_edges_1d);
		th_y = new TH1D("", ";#theta_{y}", th_y_binning_n_1d, th_y_binning_edges_1d);
		th_y_xcut = new TH1D("", ";#theta_{y}", th_y_binning_n_1d, th_y_binning_edges_1d);

		th_x_th_y = new TH2D("", ";#theta_{x};#theta_{y}", th_x_binning_n_2d, th_x_binning_edges_2d,
			th_y_binning_n_2d, th_y_binning_edges_2d);

		unsigned int N_bins;
		double *bin_edges;
		BuildBinning(anal, "ob-1-20-0.05", bin_edges, N_bins);
		t = new TH1D("", ";|t|", N_bins, bin_edges);
		delete [] bin_edges;
	}

	void Fill(double thx, double thy, signed int period)
	{
		if (!th_x)
			Init();
					
		th_x->Fill(thx);
		th_y->Fill(fabs(thy));
		
		th_x_th_y->Fill(thx, fabs(thy));

		if (thx > th_x_min && thx < th_x_max)
		{
			th_y_xcut->Fill(fabs(thy));

			map<signed int, TH1D *>::iterator it = p_th_y_xcut.find(period);
			if (it == p_th_y_xcut.end())
			{
				it = p_th_y_xcut.insert(pair<signed int, TH1D *>(period,
						new TH1D("", ";#theta_{y}", 100, 0E-6, 200E-6)
						)).first;
			}
			it->second->Fill(fabs(thy));
		}

		double p = 6.5E3;
		double t_val = p*p * (thx*thx + thy*thy);

		t->Fill(t_val);
	}

	void FillDelta(double dthx, double dthy)
	{
		if (!de_th_x)
			Init();

		de_th_x->Fill(dthx);
		de_th_y->Fill(dthy);
	}
};

//----------------------------------------------------------------------------------------------------

TH1D* MakeSimpleRatio(TH1D *num, TH1D *den, TF1 *ff, double from, double to, bool verbose = false)
{
	TH1D *rat = new TH1D(*num);
	for (int i = 1; i <= rat->GetNbinsX(); i++)
	{
		double n = num->GetBinContent(i);
		double d = den->GetBinContent(i);

		double r = (d > 0.) ? n/d : 0.;
		double v = d * r * (1. - r);
		double e = (v >= 0. && d > 0.) ? sqrt(v) / d : 0.;

		rat->SetBinContent(i, r);
		rat->SetBinError(i, e);
	}

	rat->Fit(ff, "Q", "", from, to);
	double ep = ff->GetParameter(0);
	double ep_err = ff->GetParError(0);
	
	if (verbose)
		printf("\t\tsimple fit:  %.4f +- %.4f\n", ep, ep_err);

	return rat;
}

//----------------------------------------------------------------------------------------------------

TH1D* MakeRefinedRatio(TH1D *num, TH1D *den, TF1 *ff, double from, double to, bool verbose = false)
{
	double ep = ff->GetParameter(0);
	double ep_err = ff->GetParError(0);

	// improve error calculation: si(y)^2 = N ep (1-ep)
	TH1D *rat = new TH1D(*num);
	for (int i = 1; i <= rat->GetNbinsX(); i++)
	{
		double n = num->GetBinContent(i);
		double d = den->GetBinContent(i);

		double r = (d > 0.) ? n / d : 0.;
		double v = d * ep * (1. - ep);
		double e = (v >= 0. && d > 0.) ? sqrt(v) / d : 0.;

		rat->SetBinContent(i, r);
		rat->SetBinError(i, e);
	}
	
	rat->Fit(ff, "Q", "", from, to);
	ep = ff->GetParameter(0);
	ep_err = ff->GetParError(0);
	
	if (verbose)
		printf("\t\trefined fit: %.4f +- %.4f\n", ep, ep_err);

	return rat;
}

//----------------------------------------------------------------------------------------------------

TH2D* MakeSimpleRatio(TH2D *num, TH2D *den)
{
	TH2D *rat = new TH2D(*num);
	for (int i = 1; i <= rat->GetNbinsX(); i++)
	{
		for (int j = 1; j <= rat->GetNbinsY(); j++)
		{
			double n = num->GetBinContent(i, j);
			double d = den->GetBinContent(i, j);
	
			double r = (d > 0.) ? n/d : 0.;
			double v = d * r * (1. - r);
			double e = (v >= 0. && d > 0.) ? sqrt(v) / d : 0.;
	
			rat->SetBinContent(i, j, r);
			rat->SetBinError(i, j, e);
		}
	}

	return rat;
}

//----------------------------------------------------------------------------------------------------

void PrintUsage()
{
	printf("USAGE: program <option> <option>\n");
	printf("OPTIONS:\n");
	printf("    -cfg <file>       config file\n");
	printf("    -dgn <string>     diagonal\n");
}

//----------------------------------------------------------------------------------------------------

int main(int argc, const char **argv)
{
	// defaults
	string cfg_file = "config.py";
	string diagonal_input = "";

	// parse command line
	for (int argi = 1; (argi < argc) && (cl_error == 0); ++argi)
	{
		if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0)
		{
			cl_error = 1;
			continue;
		}

		if (TestStringParameter(argc, argv, argi, "-cfg", cfg_file)) continue;
		if (TestStringParameter(argc, argv, argi, "-dgn", diagonal_input)) continue;

		printf("ERROR: unknown option '%s'.\n", argv[argi]);
		cl_error = 1;
	}

	if (cl_error)
	{
		PrintUsage();
		return 1;
	}

	// run initialisation
	if (Init(cfg_file, diagonal_input) != 0)
		return 2;

	// compatibility check
	if (cfg.diagonal == dCombined || cfg.diagonal == ad45b_56b || cfg.diagonal == ad45t_56t)
		return rcIncompatibleDiagonal;
	
	// alignment init
	for (unsigned int i = 0; i < anal.alignment_sources.size(); ++i)
	{
		printf("\n---------- alignment source %u ----------\n", i);
		anal.alignment_sources[i].Init();
	}
	printf("\n\n");

	// get input
	TChain *ch_in = new TChain("distilled");
	printf(">> input chain\n");
	for (const auto &ntupleDir : cfg.distilled_files)
	{
		string f = ntupleDir + "/distill_" + cfg.diagonal_str + ".root";
		printf("    %s\n", f.c_str());
		ch_in->Add(f.c_str());
	}
	printf("%llu entries\n", ch_in->GetEntries());

	// set up branches
	EventRed ev;
	ch_in->SetBranchAddress("timestamp", &ev.timestamp);
	ch_in->SetBranchAddress("run_num", &ev.run_num);
	ch_in->SetBranchAddress("bunch_num", &ev.bunch_num);
	ch_in->SetBranchAddress("event_num", &ev.event_num);

	ch_in->SetBranchAddress("v_L_1_F", &ev.h.L_1_F.v); ch_in->SetBranchAddress("x_L_1_F", &ev.h.L_1_F.x); ch_in->SetBranchAddress("y_L_1_F", &ev.h.L_1_F.y);
	ch_in->SetBranchAddress("v_L_2_F", &ev.h.L_2_F.v); ch_in->SetBranchAddress("x_L_2_F", &ev.h.L_2_F.x); ch_in->SetBranchAddress("y_L_2_F", &ev.h.L_2_F.y);
	ch_in->SetBranchAddress("v_R_1_F", &ev.h.R_1_F.v); ch_in->SetBranchAddress("x_R_1_F", &ev.h.R_1_F.x); ch_in->SetBranchAddress("y_R_1_F", &ev.h.R_1_F.y);
	ch_in->SetBranchAddress("v_R_2_F", &ev.h.R_2_F.v); ch_in->SetBranchAddress("x_R_2_F", &ev.h.R_2_F.x); ch_in->SetBranchAddress("y_R_2_F", &ev.h.R_2_F.y);

	// prepare output
	TFile *outF = new TFile((string("eff3outof4_") + cfg.diagonal_str + ".root").c_str(), "recreate");

	// tolerances (= 1 sigma of left-right difference)
	double si_de_th_x = 46E-6;
	double si_de_th_y = 8.5E-6;

	// vector of cut sigma multiples
	vector<double> n_si;
	n_si.push_back(1.);
	n_si.push_back(3.);
	n_si.push_back(5.);

	// studied RP combinations
	vector<string> rps;
	rps.push_back("L_2_F");
	rps.push_back("L_1_F");
	rps.push_back("R_1_F");
	rps.push_back("R_2_F");

	rps.push_back("L_1_F,R_1_F");
	rps.push_back("L_1_F,R_2_F");
	rps.push_back("L_2_F,R_1_F");
	rps.push_back("L_2_F,R_2_F");

	// book histograms
	vector< vector<HistGroup> > h_sel(rps.size(), vector<HistGroup>(n_si.size())), h_full(rps.size(), vector<HistGroup>(n_si.size()));

	// build histograms
	for (int ev_idx = 0; ev_idx < ch_in->GetEntries(); ++ev_idx)
	{
		ch_in->GetEntry(ev_idx);

		// check whether the event is to be skipped
		if (anal.SkipEvent(ev.run_num, ev.lumi_section, ev.timestamp, ev.bunch_num))
			continue;

		// apply fine alignment
		HitData h_al = ev.h;
		for (unsigned int i = 0; i < anal.alignment_sources.size(); ++i)
		{
			const AlignmentData &alData = anal.alignment_sources[i].Eval(ev.timestamp);
			h_al = h_al.ApplyAlignment(alData);
		}

		// period
		signed int period = int((ev.timestamp - anal.alignment_t0) / anal.alignment_ts);

		// loop over tested RP combinations
		for (unsigned int rpi = 0; rpi < rps.size(); rpi++)
		{
			// determine which pots are selected for event definition
			bool L_2_F = (rps[rpi].find("L_2_F") == string::npos);
			bool L_1_F = (rps[rpi].find("L_1_F") == string::npos);
			bool R_1_F = (rps[rpi].find("R_1_F") == string::npos);
			bool R_2_F = (rps[rpi].find("R_2_F") == string::npos);

			// tracks in all selected RPs?
			if ( (L_2_F && !ev.h.L_2_F.v) || (L_1_F && !ev.h.L_1_F.v) || (R_1_F && !ev.h.R_1_F.v) || (R_2_F && !ev.h.R_2_F.v) )
				continue;
			
			// tracks in all 4/4 RPs?
			bool allTracks = ev.h.L_2_F.v && ev.h.L_1_F.v && ev.h.R_1_F.v && ev.h.R_2_F.v;

			// calculate elastic kinematics for the selected tracks
			double th_y_L_sel = 0., th_x_L_sel = 0., norm_L = 0.;
			if (L_2_F) { norm_L += 1.; th_x_L_sel += -h_al.L_2_F.x / env.L_x_L_2_F; th_y_L_sel += -h_al.L_2_F.y / env.L_y_L_2_F; }
			if (L_1_F) { norm_L += 1.; th_x_L_sel += -h_al.L_1_F.x / env.L_x_L_1_F; th_y_L_sel += -h_al.L_1_F.y / env.L_y_L_1_F; }
			th_x_L_sel /= norm_L; th_y_L_sel /= norm_L;
			
			double th_y_R_sel = 0., th_x_R_sel = 0., norm_R = 0.;
			if (R_2_F) { norm_R += 1.; th_x_R_sel += +h_al.R_2_F.x / env.L_x_R_2_F; th_y_R_sel += +h_al.R_2_F.y / env.L_y_R_2_F; }
			if (R_1_F) { norm_R += 1.; th_x_R_sel += +h_al.R_1_F.x / env.L_x_R_1_F; th_y_R_sel += +h_al.R_1_F.y / env.L_y_R_1_F; }
			th_x_R_sel /= norm_R; th_y_R_sel /= norm_R;

			double th_x_sel = (th_x_R_sel + th_x_L_sel) / 2.;
			double th_y_sel = (th_y_R_sel + th_y_L_sel) / 2.;

			double de_th_x_sel = th_x_R_sel - th_x_L_sel;
			double de_th_y_sel = th_y_R_sel - th_y_L_sel;
	
			// cuts on elastic kinematics at various sigma-levels
			for (unsigned int nsi = 0; nsi < n_si.size(); nsi++)
			{
				h_sel[rpi][nsi].FillDelta(de_th_x_sel, de_th_y_sel);
			
				bool cut_th_x = (fabs(de_th_x_sel) < n_si[nsi] * si_de_th_x);
				bool cut_th_y = (fabs(de_th_y_sel) < n_si[nsi] * si_de_th_y);

				if (cut_th_x && cut_th_y)
				{
					h_sel[rpi][nsi].Fill(th_x_sel, th_y_sel, period);
			
					if (allTracks)
						h_full[rpi][nsi].Fill(th_x_sel, th_y_sel, period);
				}
			}
		}
	}

	// process and save histograms
	TF1 *ff = new TF1("ff", "[0]");

	for (unsigned int rpi = 0; rpi < rps.size(); rpi++)
	{
		printf("\n\n------------------------- excluded RPs: %s -------------------------\n", rps[rpi].c_str());

		char buf[100];
		sprintf(buf, "excluded RPs %s", rps[rpi].c_str());
		TDirectory *rpDir = outF->mkdir(buf);

		for (unsigned int nsi = 0; nsi < n_si.size(); nsi++)
		{
			printf("* n_si: %.1f\n", n_si[nsi]);

			sprintf(buf, "n_si %.1f", n_si[nsi]);
			TDirectory *nsiDir = rpDir->mkdir(buf);

			gDirectory = nsiDir;
			h_sel[rpi][nsi].de_th_x->Write("de_th_x");
			h_sel[rpi][nsi].de_th_y->Write("de_th_y");

			TCanvas *c;

			//--------------------

			gDirectory = nsiDir->mkdir("th_x dependence");
			printf("\tth_x dependence\n");
			c = new TCanvas();
			h_sel[rpi][nsi].th_x->SetName("h_sel.th_x");
			h_sel[rpi][nsi].th_x->Sumw2();
			h_sel[rpi][nsi].th_x->SetLineColor(2);
			h_sel[rpi][nsi].th_x->Draw();
			h_full[rpi][nsi].th_x->SetName("h_full.th_x");
			h_full[rpi][nsi].th_x->Sumw2();
			h_full[rpi][nsi].th_x->SetLineColor(4);
			h_full[rpi][nsi].th_x->Draw("same");
			c->Write("th_x comparison");

			TH1D *h_simple_ratio_vs_th_x = MakeSimpleRatio(h_full[rpi][nsi].th_x, h_sel[rpi][nsi].th_x, ff, -30E-6, 30E-6, false);
			h_simple_ratio_vs_th_x->SetName("h_simple_ratio.th_x");
			h_simple_ratio_vs_th_x->Write();

			TH1D *h_refined_ratio_vs_th_x = MakeRefinedRatio(h_full[rpi][nsi].th_x, h_sel[rpi][nsi].th_x, ff, -30E-6, 30E-6, false);
			h_refined_ratio_vs_th_x->SetName("h_refined_ratio.th_x");
			h_refined_ratio_vs_th_x->Write();

			//--------------------

			gDirectory = nsiDir->mkdir("th_y dependence");
			printf("\tth_y dependence\n");
			c = new TCanvas();
			h_sel[rpi][nsi].th_y->SetName("h_sel.th_y");
			h_sel[rpi][nsi].th_y->Sumw2();
			h_sel[rpi][nsi].th_y->SetLineColor(2);
			h_sel[rpi][nsi].th_y->Draw();
			h_full[rpi][nsi].th_y->SetName("h_full.th_y");
			h_full[rpi][nsi].th_y->Sumw2();
			h_full[rpi][nsi].th_y->SetLineColor(4);
			h_full[rpi][nsi].th_y->Draw("same");
			c->Write("th_y comparison");

			TH1D *h_simple_ratio_vs_th_y = MakeSimpleRatio(h_full[rpi][nsi].th_y, h_sel[rpi][nsi].th_y, ff, 10E-6, 90E-6, false);
			h_simple_ratio_vs_th_y->SetName("h_simple_ratio.th_y");
			h_simple_ratio_vs_th_y->Write();

			TH1D *h_refined_ratio_vs_th_y = MakeRefinedRatio(h_full[rpi][nsi].th_y, h_sel[rpi][nsi].th_y, ff, 10E-6, 90E-6, false);
			h_refined_ratio_vs_th_y->SetName("h_refined_ratio.th_y");
			h_refined_ratio_vs_th_y->Write();

			//--------------------

			gDirectory = nsiDir->mkdir("th_y dependence with th_x cut");
			printf("\tth_y dependence with th_x cut\n");
			c = new TCanvas();
			h_sel[rpi][nsi].th_y_xcut->SetName("h_sel.th_y");
			h_sel[rpi][nsi].th_y_xcut->Sumw2();
			h_sel[rpi][nsi].th_y_xcut->SetLineColor(2);
			h_sel[rpi][nsi].th_y_xcut->Draw();
			h_full[rpi][nsi].th_y_xcut->SetName("h_full.th_y");
			h_full[rpi][nsi].th_y_xcut->Sumw2();
			h_full[rpi][nsi].th_y_xcut->SetLineColor(4);
			h_full[rpi][nsi].th_y_xcut->Draw("same");
			c->Write("th_y comparison");

			TH1D *h_simple_ratio_vs_th_y_cut = MakeSimpleRatio(h_full[rpi][nsi].th_y_xcut, h_sel[rpi][nsi].th_y_xcut, ff, 10E-6, 90E-6, true);
			h_simple_ratio_vs_th_y_cut->SetName("h_simple_ratio.th_y");
			h_simple_ratio_vs_th_y_cut->Write();

			TH1D *h_refined_ratio_vs_th_y_cut = MakeRefinedRatio(h_full[rpi][nsi].th_y_xcut, h_sel[rpi][nsi].th_y_xcut, ff, 10E-6, 90E-6, true);
			h_refined_ratio_vs_th_y_cut->SetName("h_refined_ratio.th_y");
			h_refined_ratio_vs_th_y_cut->Write();

			//--------------------

			gDirectory = nsiDir->mkdir("th_x, th_y dependence");
			h_sel[rpi][nsi].th_x_th_y->SetName("h_sel.th_x_th_y");
			h_sel[rpi][nsi].th_x_th_y->Write();
			h_full[rpi][nsi].th_x_th_y->SetName("h_full.th_x_th_y");
			h_full[rpi][nsi].th_x_th_y->Write();

			TH2D *h_simple_ratio_vs_th_x_th_y = MakeSimpleRatio(h_full[rpi][nsi].th_x_th_y, h_sel[rpi][nsi].th_x_th_y);
			h_simple_ratio_vs_th_x_th_y->SetName("h_simple_ratio_vs_th_x_th_y");
			h_simple_ratio_vs_th_x_th_y->Write();
			
			//--------------------
			
			gDirectory = nsiDir->mkdir("th_y dependence with th_x cut, per period");
			map<signed int, TH1D *> &m_sel = h_sel[rpi][nsi].p_th_y_xcut;
			map<signed int, TH1D *> &m_full = h_full[rpi][nsi].p_th_y_xcut;

			TGraphErrors *g_eff_vs_time = new TGraphErrors();
			g_eff_vs_time->SetName("g_eff_vs_time");

			TF1 *f_const = new TF1("f_const", "[0]");
			
			for (map<signed int, TH1D *>::iterator it = m_sel.begin(); it != m_sel.end(); ++it)
			{
				signed int period = it->first;
				double timestamp = (double(period) + 0.5) * anal.alignment_ts + anal.alignment_t0;

				TH1D *h_sel = m_sel[period];
				TH1D *h_full = m_full[period];

				if (!h_sel || !h_full)
					continue;

				TH1D *h_ratio = new TH1D(*h_full);
				for (int bi = 1; bi < h_ratio->GetNbinsX(); bi++)
				{
					double N_sel = h_sel->GetBinContent(bi);
					double N_full = h_full->GetBinContent(bi);
					double p = (N_sel > 0.) ? N_full / N_sel : 0.;
					double v = p * (1. - p);
					double s = (v > 0. && N_sel > 0.) ? sqrt(v / N_sel) : 0.;

					h_ratio->SetBinContent(bi, p);
					h_ratio->SetBinError(bi, s);
				}

				h_ratio->Fit(f_const, "Q", "", 10E-6, 90E-6);

				double eff = f_const->GetParameter(0);
				double eff_u = f_const->GetParError(0);
				
				char buf[100];
				sprintf(buf, "h_ratio, period=%i", period);
				h_ratio->SetName(buf);
				h_ratio->Write();

				delete h_ratio;

				int idx = g_eff_vs_time->GetN();
				g_eff_vs_time->SetPoint(idx, timestamp, eff);
				g_eff_vs_time->SetPointError(idx, 0., eff_u);
			}

			g_eff_vs_time->Write();

			delete f_const;

			//--------------------

			gDirectory = nsiDir->mkdir("t dependence");
			printf("\tt dependence\n");
			c = new TCanvas();
			h_sel[rpi][nsi].t->SetName("h_sel.t");
			h_sel[rpi][nsi].t->Sumw2();
			h_sel[rpi][nsi].t->SetLineColor(2);
			h_sel[rpi][nsi].t->Draw();
			h_full[rpi][nsi].t->SetName("h_full.t");
			h_full[rpi][nsi].t->Sumw2();
			h_full[rpi][nsi].t->SetLineColor(4);
			h_full[rpi][nsi].t->Draw("same");
			c->Write("t comparison");
		}
	}
	
	return 0;
}
