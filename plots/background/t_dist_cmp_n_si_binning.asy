import root;
import pad_layout;
include "../common.asy";

string dataset = "fill7280/Totem1";

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };

string binnings[] = {
	"sb1",
};

string histogram = "acceptance correction/<binning>/h_t_after";

string combinations[];
pen comb_pens[];

//combinations.push("n_si=2"); comb_pens.push(black);
combinations.push("n_si=3"); comb_pens.push(red);
combinations.push("n_si=4"); comb_pens.push(blue);
combinations.push("n_si=5"); comb_pens.push(heavygreen);
//combinations.push("n_si=6"); comb_pens.push(magenta);

string ref_comb = "n_si=4";

xSizeDef = 10cm;

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

void PlotRatio(RootObject o, RootObject r, pen p)
{
	int N = r.iExec("GetNbinsX");
	for (int i = 1; i <= N; ++i)
	{
		real c = r.rExec("GetBinCenter", i);
		real w = r.rExec("GetBinWidth", i);

		real v = o.rExec("GetBinContent", i);
		real u = o.rExec("GetBinError", i);

		real v_r = r.rExec("GetBinContent", i);
		real u_r = r.rExec("GetBinError", i);

		real ratio = (v_r != 0) ? (v / v_r - 1.) * 100.: 0.;
		//real ratio_unc = (u > 0. && u_r > 0.) ? v / v_r * 100 * sqrt( (u/v)^2 + (u_r/v_r)^2 ) : 0.;
		real ratio_unc = 0.;

		draw(Scale((c, ratio)), mCi+p);
		draw(Scale((c, ratio-ratio_unc))--Scale((c, ratio+ratio_unc)), p);
		draw(Scale((c-w/2, ratio))--Scale((c+w/2, ratio)), p);
	}
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

for (int bi : binnings.keys)
{
	string hist_path = replace(histogram, "<binning>", binnings[bi]);

	for (int dgi : diagonals.keys)
	{
		NewRow();

		string diagonal = diagonals[dgi];

		NewPad(false);
		label(replace("{\SetFontSizesXX\vbox{\hbox{"+dataset+"}\hbox{"+dgn_labels[dgi]+"}\hbox{" + binnings[bi] + "}}}", "_", "\_"));

		//--------------------

		NewPad("$|t|\ung{GeV^2}$", "$\d\sigma/\d t\ung{mb/GeV^2}$");
		scale(Linear, Log);
		for (int ci : combinations.keys)
		{
			string label = replace(combinations[ci], "_", "\_");
			if (combinations[ci] == ref_comb)
				label += " (reference)";
		
			string f = topDir+"studies/background/"+dataset+"/"+combinations[ci]+"/distributions_"+diagonal+".root";
			draw(RootGetObject(f, hist_path), "eb", comb_pens[ci], label);
		}
		
		frame fLegend = BuildLegend();
		
		limits((0, 1e6), (0.04, 1e8), Crop);

		//--------------------

		NewPad("$|t|\ung{GeV^2}$", "$\d\sigma/\d t\ung{mb/GeV^2}$");
		scale(Linear, Log);
		currentpad.xTicks = LeftTicks(0.005, 0.001);

		for (int ci : combinations.keys)
		{
			string label = replace(combinations[ci], "_", "\_");
			if (combinations[ci] == ref_comb)
				label += " (reference)";
		
			string f = topDir+"studies/background/"+dataset+"/"+combinations[ci]+"/distributions_"+diagonal+".root";
			draw(RootGetObject(f, hist_path), "eb", comb_pens[ci], label);
		}
		
		frame fLegend = BuildLegend();
		
		limits((0, 1e6), (0.04, 1e8), Crop);

		//--------------------
		
		NewPad(false);
		attach(fLegend);
		
		//--------------------
		
		string ref_f = topDir+"studies/background/"+dataset+"/"+ref_comb+"/distributions_"+diagonal+".root";
		RootObject ref_o = RootGetObject(ref_f, hist_path);
		
		//--------------------

		NewPad("$|t|\ung{GeV^2}$", "$\d\sigma/\d t$: (test - ref) / ref$\ung{\%}$");
		for (int ci : combinations.keys)
		{
			//if (combinations[ci] == ref_comb)
			//	continue;
		
			string f = topDir+"studies/background/"+dataset+"/"+combinations[ci]+"/distributions_"+diagonal+".root";
			RootObject o = RootGetObject(f, hist_path);
			PlotRatio(o, ref_o, comb_pens[ci]);
		}
		
		limits((0, -10), (0.04, 10), Crop);
		
		//--------------------

		NewPad("$|t|\ung{GeV^2}$", "$\d\sigma/\d t$: (test - ref) / ref$\ung{\%}$");
		for (int ci : combinations.keys)
		{
			//if (combinations[ci] == ref_comb)
			//	continue;
		
			string f = topDir+"studies/background/"+dataset+"/"+combinations[ci]+"/distributions_"+diagonal+".root";
			RootObject o = RootGetObject(f, hist_path);
			PlotRatio(o, ref_o, comb_pens[ci]);
		}
		
		limits((0, -1), (0.04, 3), Crop);
	}
}
