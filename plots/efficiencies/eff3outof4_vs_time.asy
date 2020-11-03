import root;
import pad_layout;
include "../run_info.asy";

string topDir = "../../";

string datasets[], fills[];
//datasets.push("DS-fill7280/Totem1"); fills.push("7280");
datasets.push("DS-fill7281/Totem1"); fills.push("7281");
//datasets.push("DS-fill7282/Totem1"); fills.push("7282");
//datasets.push("DS-fill7283/Totem1"); fills.push("7283");
//datasets.push("DS-fill7284/Totem1"); fills.push("7284");
//datasets.push("DS-fill7285/Totem1"); fills.push("7285");
//datasets.push("DS-fill7286/Totem1"); fills.push("7286");
//datasets.push("DS-fill7287/Totem1"); fills.push("7287");
//datasets.push("DS-fill7288/Totem1"); fills.push("7288");
datasets.push("DS-fill7289/Totem1"); fills.push("7289");
//datasets.push("DS-fill7290/Totem1"); fills.push("7290");
datasets.push("DS-fill7291/Totem1"); fills.push("7291");

string diagonals[];
diagonals.push("45b_56t");
diagonals.push("45t_56b");

string rps[], rp_labels[];
rps.push("L_2_F"); rp_labels.push("45-220-fr");
rps.push("L_1_F"); rp_labels.push("45-210-fr");
rps.push("R_1_F"); rp_labels.push("56-210-fr");
rps.push("R_2_F"); rp_labels.push("56-220-fr" );

yTicksDef = RightTicks(1., 0.2);
xTicksDef = LeftTicks(1., 0.5);

TGraph_errorBar = None;


//----------------------------------------------------------------------------------------------------

void SetPadWidth()
{
	real factorHoursToSize = 3cm / 3;

	real timespan = currentpicture.userMax2().x - currentpicture.userMin2().x;
	currentpad.xSize = timespan * factorHoursToSize;
}

//----------------------------------------------------------------------------------------------------

frame f_legend;

for (int rpi : rps.keys)
{
	NewRow();

	NewPad(drawAxes=false);
	label("{\SetFontSizesXX " + rp_labels[rpi] + "}");

	for (int dsi : datasets.keys)
	{
		NewPad("time $\ung{h}$", "efficiency\ung{\%}");
		real y_min = 95, y_max = 100;

		DrawRunBands(fills[dsi], y_min, y_max);

		for (int dgi : diagonals.keys)
		{
			string f = topDir + datasets[dsi] + "/eff3outof4_"+diagonals[dgi]+".root";
			string d = "excluded RPs " + rps[rpi] + "/n_si 3.0";

			pen p = StdPen(dgi+1);

			string label = replace(diagonals[dgi], "_", " -- ");

			draw(swToHours * scale(1, 100), RootGetObject(f, d+"/th_y dependence with th_x cut, per period/g_eff_vs_time"),
				"p", p, mCi+2pt+p, label);
		}

		ylimits(y_min, y_max, Crop);

		SetPadWidth();
	}

	f_legend = BuildLegend();
}

NewPad(false);
add(f_legend);