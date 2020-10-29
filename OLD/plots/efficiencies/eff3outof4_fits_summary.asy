import root;
import pad_layout;

string topDir = "../../";

string datasets[], fills[];
datasets.push("DS-fill7280/Totem1"); fills.push("7280");
datasets.push("DS-fill7281/Totem1"); fills.push("7281");
datasets.push("DS-fill7282/Totem1"); fills.push("7282");
datasets.push("DS-fill7283/Totem1"); fills.push("7283");
datasets.push("DS-fill7284/Totem1"); fills.push("7284");
datasets.push("DS-fill7285/Totem1"); fills.push("7285");
datasets.push("DS-fill7286/Totem1"); fills.push("7286");
datasets.push("DS-fill7287/Totem1"); fills.push("7287");
datasets.push("DS-fill7288/Totem1"); fills.push("7288");
datasets.push("DS-fill7289/Totem1"); fills.push("7289");
datasets.push("DS-fill7290/Totem1"); fills.push("7290");
datasets.push("DS-fill7291/Totem1"); fills.push("7291");

string diagonals[];
diagonals.push("45b_56t");
diagonals.push("45t_56b");

string rps[], rp_labels[];
rps.push("L_2_F"); rp_labels.push("45-220-fr");
rps.push("L_1_F"); rp_labels.push("45-210-fr");
rps.push("R_1_F"); rp_labels.push("56-210-fr");
rps.push("R_2_F"); rp_labels.push("56-220-fr" );

xSizeDef = 6cm;
ySizeDef = 5cm;

//yTicksDef = RightTicks(5., 1.);

//----------------------------------------------------------------------------------------------------

string TicksDataset(real x)
{
	int xi = (int) x;
	if (xi < 0 || xi >= datasets.length)
		return "";

	return datasets[xi];
}

xTicksDef = LeftTicks(rotate(90)*Label(""), TicksDataset, 1., 1.);

//----------------------------------------------------------------------------------------------------

NewPad(false);

for (int dgi : diagonals.keys)
{
	NewPad(false);
	label("{\SetFontSizesXX " + replace(diagonals[dgi], "_", "\_") + "}");

	NewPad(false);
}

for (int rpi : rps.keys)
{
	NewRow();

	NewPad(false);
	label("{\SetFontSizesXX " + rp_labels[rpi] + "}");

	for (int dgi : diagonals.keys)
	{
		pad p_a = NewPad("", "slope$\ung{rad^{-1}}$");
		pad p_b = NewPad("", "intercept$\ung{\%}$");

		// plot fits per dataset
		for (int dsi : datasets.keys)
		{
			if (rp_labels[rpi] == "L-220-fr" && diagonals[dgi] == "45t_56b" && datasets[dsi] == "DS-fill5317")
				continue;

			string f = topDir + datasets[dsi] + "/eff3outof4_fit.root";
			string d = diagonals[dgi] + "/" + rps[rpi];
			RootObject fit = RootGetObject(f, d+"/pol1");

			real a = fit.rExec("GetParameter", 1), a_unc = fit.rExec("GetParError", 1);
			real b = fit.rExec("GetParameter", 0)*100, b_unc = fit.rExec("GetParError", 0)*100;

			b_unc = 0.5;

			real x = dsi;

			SetPad(p_a);
			draw((x, a), mCi+red+2pt);
			draw((x, a-a_unc)--(x, a+a_unc), red);

			SetPad(p_b);
			draw((x, b), mCi+blue+2pt);
			draw((x, b-b_unc)--(x, b+b_unc), blue);
		}

		// get global fits	
		/*
		string f = topDir + "efficiency_fits/global_fit.root";
		string d = diagonals[dgi] + "/" + rps[rpi];
		RootObject fit_gl = RootGetObject(f, d+"/pol1");
		
		real a_g = fit_gl.rExec("GetParameter", 1), a_g_unc = fit_gl.rExec("GetParError", 1);
		real b_g = fit_gl.rExec("GetParameter", 0)*100, b_g_unc = fit_gl.rExec("GetParError", 0)*100;

		// finalise pads
		SetPad(p_a);
		currentpad.yTicks = RightTicks(50., 10.);
		string avg_label = format("global fit: $%#.1f$", a_g) + format("$\pm %#.1f$", a_g_unc);
		draw((-0.5, a_g)--(datasets.length-0.5, a_g), red, avg_label);
		limits((-1, -200), (datasets.length, +0), Crop);
		AttachLegend();

		SetPad(p_b);
		currentpad.yTicks = RightTicks(1., 0.5);
		string avg_label = format("global fit: $%#.1f$", b_g) + format("$\pm %#.1f$", b_g_unc);
		draw((-0.5, b_g)--(datasets.length-0.5, b_g), blue, avg_label);
		limits((-1, 94), (datasets.length, 100), Crop);
		AttachLegend();
		*/
	}
}

GShipout("eff3outof4_fits_summary", vSkip=0pt);