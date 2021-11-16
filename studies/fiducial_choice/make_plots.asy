import root;
import pad_layout;

string topDir = "../../data/all-good/Totem1/";

string dgns[], d_labels[];
dgns.push("45b_56t"); d_labels.push("45 bot -- 56 top");
dgns.push("45t_56b"); d_labels.push("45 top -- 56 bot");

real p_beam = 450.;

real t1 = 0.0170;
real t2 = 0.0215;
real t3 = 0.0250;

//----------------------------------------------------------------------------------------------------

real GetNormalisation(RootObject hist)
{
	int bi_min = hist.iExec("FindBin", 0.003);
	int bi_max = hist.iExec("FindBin", 0.005);

	write(bi_min, bi_max);

	real s = 0.;

	for (int bi = bi_min; bi <= bi_max; ++bi)
	{
		s += hist.rExec("GetBinContent", bi);
	}

	return s;
}

//----------------------------------------------------------------------------------------------------

void DrawEyeGuide(real y_ref)
{
	real B = 17;

	guide g;

	for (real t = 0; t <= 0.025; t += 0.025)
		g = g -- Scale((t, y_ref * exp(-B * (t - 0.005))));

	pen p = 0.9*gray + 0.1*green;
	draw(g, p + 3pt, "guide, $B = 17$");
}

//----------------------------------------------------------------------------------------------------

void DrawOne(string fn, string tests[])
{
	for (int dgni : dgns.keys)
	{
		NewRow();

		NewPadLabel(d_labels[dgni]);

		NewPad("$x^*$", xSize=3cm);
		for (int ti : tests.keys)
			draw(RootGetObject(topDir + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "selected - vertex/h_vtx_x"), "vl", StdPen(ti));
		xlimits(-2, +2, Crop);

		NewPad("$y^*$", xSize=3cm);
		for (int ti : tests.keys)
			draw(RootGetObject(topDir + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "selected - vertex/h_vtx_y"), "vl", StdPen(ti));

		NewPad("$\th_x^*\ung{\mu rad}$", "$\th_y^*\ung{\mu rad}$", xTicks = LeftTicks(100., 50.), xSize = 6cm);
		for (int ti : tests.keys)
		{
			draw(scale(1e6, 1e6), RootGetObject(topDir + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "fiducial cuts/fc_G"), "l", StdPen(ti));
			draw(scale(1e6, 1e6), RootGetObject(topDir + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "fiducial cuts/fc_L"), "l", StdPen(ti) + dashed);
		}

		draw(scale(sqrt(t1) / p_beam * 1e6) * unitcircle, cyan + dashed);
		draw(scale(sqrt(t2) / p_beam * 1e6) * unitcircle, magenta + dashed);
		draw(scale(sqrt(t3) / p_beam * 1e6) * unitcircle, orange + dashed);

		if (dgns[dgni] == "45b_56t")
			limits((-380, 30), (+380, 135), Crop);
		else
			limits((-380, -135), (+380, -30), Crop);

		// -----

		NewPad("$|t|\ung{GeV^2}$", xSize=10cm, xTicks = LeftTicks(0.005, 0.001));
		scale(Linear, Log);
		real norm_ref = -1;
		real y_ref = -1;
		for (int ti : tests.keys)
		{
			pen p = StdPen(ti);
			if (ti == 0)
				p += 1pt;

			RootObject hist = RootGetObject(topDir + tests[ti] + "/distributions_" + dgns[dgni] + ".root", "normalization/sb1/h_t_normalized");
			real norm = GetNormalisation(hist);

			real scale = 1.;
			if (norm_ref < 0)
			{
				norm_ref = norm;
				y_ref = hist.rExec("GetBinContent", hist.iExec("FindBin", 0.005));
				DrawEyeGuide(y_ref);
			} else {
				scale = norm_ref / norm;
			}

			string option = (ti == 0) ? "vl,eb" : "eb";

			draw(shift(0, log10(scale)), hist, option, p);
			AddToLegend(replace(tests[ti], "_", "\_") + format(", entries $%.1f \times 10^5$", hist.rExec("GetEntries") / 1e5), mPl+4pt+p);
		}

		limits((0, y_ref/2), (0.025, y_ref*1.5), Crop);

		yaxis(XEquals(t1, false), cyan + dashed);
		yaxis(XEquals(t2, false), magenta + dashed);
		yaxis(XEquals(t3, false), orange + dashed);

		AttachLegend(BuildLegend(NW), NE);
	}

	GShipout(fn, hSkip=0mm, vSkip=0mm);
}

//----------------------------------------------------------------------------------------------------

/*
string tests[] = new string[] { "default" };
DrawOne("default", tests);

string tests[] = new string[] { "default", "vtx_x_low", "vtx_x_mid", "vtx_x_hig" };
DrawOne("vtx_x", tests);

string tests[] = new string[] { "default", "vtx_y_low", "vtx_y_mid", "vtx_y_hig" };
DrawOne("vtx_y", tests);

//string tests[] = new string[] { "default", "vtx_x_y_mid" };
//DrawOne("vtx_x_y", tests);

string tests[] = new string[] { "default", "th_x_low", "th_x_mid", "th_x_hig" };
//string tests[] = new string[] { "default", "th_x_low", "th_x_TEST" };
DrawOne("th_x", tests);

string tests[] = new string[] { "default", "th_x_test1", "th_x_test1b" };
DrawOne("th_x_test_a", tests);

string tests[] = new string[] { "default", "th_x_test2", "th_x_test3" };
DrawOne("th_x_test_b", tests);

string tests[] = new string[] { "default", "th_x_test4", "th_x_test5" };
DrawOne("th_x_test_c", tests);

string tests[] = new string[] { "default", "th_y_low", "th_y_low_mid", "th_y_hig" };
DrawOne("th_y", tests);

string tests[] = new string[] { "default", "th_y_test1", "th_y_test2", "th_y_test3", "th_y_test4" };
DrawOne("th_y_test_a", tests);

//string tests[] = new string[] { "default", "opt1", "opt2", "opt3" };
//DrawOne("opt", tests);
*/

//string tests[] = new string[] { "default", "default_shrink_32_8" };
//DrawOne("shrink", tests);

string tests[] = new string[] { "default", "default_d_x_adj_2.5", "default_d_y_adj_1.2" };
DrawOne("smear_corr", tests);
