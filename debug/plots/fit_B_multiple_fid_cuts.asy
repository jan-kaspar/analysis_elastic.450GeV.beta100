import root;
import pad_layout;

string topDir = "../";

string f = topDir + "fit_B.root";

string fid_cuts[] = {
	"default",
    "th_x_low", "th_x_mid", "th_x_hig",
	"th_y_low", "th_y_low_mid", "th_y_hig",
    "vtx_x_low", "vtx_x_mid", "vtx_x_hig",
	"vtx_y_low", "vtx_y_mid", "vtx_y_hig",
	//"vtx_x_y_mid",
	//"opt1", "opt2", "opt3",
};

string diagonals[] = {
	"45b_56t",
	"45t_56b",
};

string ranges[];
pen r_pens[];
ranges.push("0.005_0.010"); r_pens.push(blue);
ranges.push("0.010_0.015"); r_pens.push(red);
ranges.push("0.015_0.020"); r_pens.push(heavygreen);
ranges.push("0.020_0.025"); r_pens.push(magenta);

string range_ref = "0.005_0.025";

//----------------------------------------------------------------------------------------------------

void DrawRef(real y_ref, real t_ref, real B, pen p)
{
	guide g;

	for (real t = 0; t <= 0.026; t += 0.0025)
	{
		real y = y_ref * exp(-B * (t - t_ref));
		g = g--((t, y));
	}

	draw(g, p, format("reference, B = %.1f", B));
}

//----------------------------------------------------------------------------------------------------

NewPadLabel("");

for (string diagonal : diagonals)
	NewPadLabel(replace(diagonal, "_", "\_"));

for (int fdi : fid_cuts.keys)
{
	NewRow();

	NewPadLabel(replace(fid_cuts[fdi], "_", "\_"));

	for (string diagonal : diagonals)
	{
		string dataset = "all-good_" + fid_cuts[fdi] + "_" + diagonal;

		NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");

		RootObject fit_ref = RootGetObject(f, dataset + "/fit_range_" + range_ref);
		real t_ref = 0.005;
		real y_ref = fit_ref.rExec("Eval", t_ref);
		DrawRef(y_ref, t_ref, 17., gray+2pt);

		RootObject hist = RootGetObject(f, dataset + "/h_dsdt");
		draw(hist, "eb", black);
		
		for (int ri : ranges.keys)
		{
			RootObject fit = RootGetObject(f, dataset + "/fit_range_" + ranges[ri]);
			real B = fit.rExec("GetParameter", 1);
			real B_unc = fit.rExec("GetParError", 1);

			string l = format("$B = %.2f \pm ", B) + format("%.2f$", B_unc);

			draw(fit, r_pens[ri], l);
		}

		limits((0, y_ref/2), (0.025, y_ref*2), Crop);
		//xlimits(0, 0.025, Crop);

		//AttachLegend(BuildLegend(replace(dataset, "_", "-"), S), N);
		AttachLegend();
	}
}

GShipout(vSkip = 0mm);
