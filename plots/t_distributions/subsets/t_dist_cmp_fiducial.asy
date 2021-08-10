import root;
import pad_layout;
include "../../common.asy";

string dgns[], d_labels[];
dgns.push("45b_56t"); d_labels.push("45 bot -- 56 top");
dgns.push("45t_56b"); d_labels.push("45 top -- 56 bot");

//----------------------------------------------------------------------------------------------------

real GetNormalisationFactor(RootObject h, real x_min, real x_max, real s_ref = 1.)
{
	int bi_min = h.iExec("FindBin", x_min);
	int bi_max = h.iExec("FindBin", x_max);

	real s = 0;
	for (int bi = bi_min; bi <= bi_max; ++bi)
		s += h.rExec("GetBinContent", bi) * h.rExec("GetBinWidth", bi);

	return s_ref / s;
}

//----------------------------------------------------------------------------------------------------

real dsdt_ref(real t)
{
	return 3.75 * exp(-16.0 * t);
}

//----------------------------------------------------------------------------------------------------

void DrawOne(string fn, string con, string con_h_lab, string con_v_lab, string tests[])
{
	for (int dgni : dgns.keys)
	{
		NewRow();

		NewPadLabel(d_labels[dgni]);

		string bd = topDir + "data/all-good/Totem1/";
		

		/*
		NewPad(con_h_lab, con_v_lab);
		for (int ti : tests.keys)
		{
			pen p = StdPen(ti);

			RootObject obj = RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", con);
			if (obj.InheritsFrom("TH1"))
				draw(obj, "vl", p);
			if (obj.InheritsFrom("TGraph"))
				draw(scale(1e6, 1e6), obj, "l", p);
		}

		if (find(fn, "th_") == 0)
		{
			currentpad.xTicks = LeftTicks(100., 50.);
			currentpad.xSize = 10cm;
		}
		*/

		// vtx_x plot

		NewPad("$x^*$");
		for (int ti : tests.keys)
			draw(RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "selected - vertex/h_vtx_x"), "vl", StdPen(ti));

		// vtx_y plot

		NewPad("$y^*$");
		for (int ti : tests.keys)
			draw(RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "selected - vertex/h_vtx_y"), "vl", StdPen(ti));

		// th*_y vs th*_x plot

		NewPad("$\th_x^*\ung{\mu rad}$", "$\th_y^*\ung{\mu rad}$", xTicks = LeftTicks(100., 50.), xSize = 8cm);
		for (int ti : tests.keys)
		{
			draw(scale(1e6, 1e6), RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "fiducial cuts/fc_L"), "l", StdPen(ti) + dashed);
			draw(scale(1e6, 1e6), RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "fiducial cuts/fc_G"), "l", StdPen(ti));
		}

		// t dist plot

		NewPad("$|t|\ung{GeV^2}$", xSize=10cm, xTicks = LeftTicks(0.005, 0.001));
		scale(Linear, Log);

		RootObject fit_ref;
		real nf_ref;

		for (int ti : tests.keys)
		{
			pen p = StdPen(ti);

			string f = bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root";
			string obj = "normalization/sb1/h_t_normalized";
			RootObject h = RootGetObject(f, obj);

			real nf = GetNormalisationFactor(h, 0.0025, 0.0050, 0.01);

			if (tests[ti] == "default")
			{
				fit_ref = RootGetObject(f, obj + "|expo");
				nf_ref = nf;
			}

			draw(shift(0, log10(nf)), h, "eb", p);
			AddToLegend(replace(tests[ti], "_", "\_"), mPl+4pt+p);
		}

		TF1_x_min = 0;
		TF1_x_max = 0.03;
		draw(shift(0, log10(nf_ref)), fit_ref, black+1pt);

		draw(graph(dsdt_ref, 0, 0.03), magenta+dashed);

		limits((0, 2e0), (0.03, 4e1), Crop);
		AttachLegend();

		// theta*_x dist plot
		/*
		NewPad("$\th_x^*\ung{\mu rad}$", "", xTicks = LeftTicks(200., 100.));
		for (int ti : tests.keys)
		{
			RootObject hist = RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "selected - angles/h_th_x");
			real nf = GetNormalisationFactor(hist, -50e-6, +50e-6);
			draw(scale(1e6, nf), hist, "vl", StdPen(ti));
		}

		// theta*_y dist plot
		NewPad("$\th_y^*\ung{\mu rad}$", "", xTicks = LeftTicks(50., 10.));
		for (int ti : tests.keys)
		{
			RootObject hist = RootGetObject(bd + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "selected - angles/h_th_y");

			real nf = 0;
			if (dgns[dgni] == "45b_56t")
				nf = GetNormalisationFactor(hist, 40e-6, 60e-6);
			else
				nf = GetNormalisationFactor(hist, -60e-6, -40e-6);

			draw(scale(1e6, nf), hist, "vl", StdPen(ti));
		}

		if (dgns[dgni] == "45b_56t")
			xlimits(0, +150, Crop);
		else
			xlimits(-150, 0, Crop);
		*/
	}

	GShipout(fn);
}

//----------------------------------------------------------------------------------------------------

/*
string tests[] = new string[] { "default", "vtx_x_low", "vtx_x_mid", "vtx_x_hig" };
DrawOne("t_dist_cmp_fiducial_vtx_x", "selected - vertex/h_vtx_x", "$x^*$", "", tests);

string tests[] = new string[] { "default", "vtx_y_low", "vtx_y_mid", "vtx_y_hig" };
DrawOne("t_dist_cmp_fiducial_vtx_y", "selected - vertex/h_vtx_y", "$y^*$", "", tests);

string tests[] = new string[] { "default", "vtx_x_y_mid" };
DrawOne("t_dist_cmp_fiducial_vtx_x_y", "selected - vertex/h_vtx_y", "$y^*$", "", tests);

string tests[] = new string[] { "default", "th_x_low", "th_x_mid", "th_x_hig" };
DrawOne("t_dist_cmp_fiducial_th_x", "fiducial cuts/fc_G", "$\th_x^*\ung{\mu rad}$", "$\th_y^*\ung{\mu rad}$", tests);

string tests[] = new string[] { "default", "th_y_low", "th_y_low_mid", "th_y_hig" };
DrawOne("t_dist_cmp_fiducial_th_y", "fiducial cuts/fc_G", "$\th_x^*\ung{\mu rad}$", "$\th_y^*\ung{\mu rad}$", tests);
*/

string tests[] = new string[] { "default", "opt1", "opt2", "opt3" };
DrawOne("t_dist_cmp_fiducial_opt", "fiducial cuts/fc_G", "$\th_x^*\ung{\mu rad}$", "$\th_y^*\ung{\mu rad}$", tests);
