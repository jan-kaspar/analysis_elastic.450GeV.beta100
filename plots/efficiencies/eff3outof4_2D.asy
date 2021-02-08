import root;
import pad_layout;

string topDir = "../../";

string datasets[], fills[];
//datasets.push("data/fill7280/Totem1"); fills.push("7280");
datasets.push("data/fill7281/Totem1"); fills.push("7281");
//datasets.push("data/fill7282/Totem1"); fills.push("7282");
//datasets.push("data/fill7283/Totem1"); fills.push("7283");
//datasets.push("data/fill7284/Totem1"); fills.push("7284");
//datasets.push("data/fill7285/Totem1"); fills.push("7285");
//datasets.push("data/fill7286/Totem1"); fills.push("7286");
//datasets.push("data/fill7287/Totem1"); fills.push("7287");
//datasets.push("data/fill7288/Totem1"); fills.push("7288");
//datasets.push("data/fill7289/Totem1"); fills.push("7289");
//datasets.push("data/fill7290/Totem1"); fills.push("7290");
datasets.push("data/fill7291/Totem1"); fills.push("7291");

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
//xTicks=LeftTicks(format="$$", 20., 10.)
xTicksDef = LeftTicks(50., 10.);

int gx=0, gy=0;

TH2_palette = Gradient(blue, heavygreen, yellow, red);
TH2_z_min = 0;
TH2_z_max = 1.;

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	for (int dgi : diagonals.keys)
	{
		string f = topDir + datasets[dsi] + "/eff3outof4_" + diagonals[dgi] + ".root";
		real sgn = +1;
		string opt = "vl,eb";
		
		++gy; gx = 0;
		for (int rpi : rps.keys)
		{
			++gx;
			NewPad(false, gx, gy);
			label("{\SetFontSizesXX " + rp_labels[rpi] + "}");
		}
		
		NewPad(false, -1, gy);
		label(replace("\vbox{\SetFontSizesXX\hbox{dataset: "+datasets[dsi]+"}\hbox{diagonal: "+diagonals[dgi]+"}}", "_", "\_"));

		++gy; gx = 0;
		NewPad(false, -1, gy);	
		label("{\SetFontSizesXX efficiency}");

		for (int rpi : rps.keys)
		{
			string d = "excluded RPs " + rps[rpi] + "/n_si 3.0";

			TH2_z_min = 0.9; TH2_z_max = 1.0;
			TH2_paletteTicks = PaletteTicks(Step=0.02, step=0.01);

			++gx;
			NewPad("$\th_x^*\ung{\mu rad}$", "$\th_y^*\ung{\mu rad}$", gx, gy, axesAbove=true);
			draw(scale(1e6, 1e6*sgn), RootGetObject(f, d+"/th_x, th_y dependence/h_simple_ratio_vs_th_x_th_y"), "def");

			limits((-150, 0), (150, 110), Crop);
		}
	}
}

GShipout("eff3outof4_2D", vSkip=0pt);
