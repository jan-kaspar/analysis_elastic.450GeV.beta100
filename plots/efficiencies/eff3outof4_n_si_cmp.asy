import root;
import pad_layout;
include "../common.asy";

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
datasets.push("data/fill7289/Totem1"); fills.push("7289");
//datasets.push("data/fill7290/Totem1"); fills.push("7290");
datasets.push("data/fill7291/Totem1"); fills.push("7291");

string diagonals[];
diagonals.push("45b_56t");
diagonals.push("45t_56b");

string rps[], rp_labels[];
rps.push("L_2_F"); rp_labels.push("45-220-fr");
rps.push("L_1_F"); rp_labels.push("45-210-fr");
rps.push("R_1_F"); rp_labels.push("56-210-fr");
rps.push("R_2_F"); rp_labels.push("56-220-fr");

string n_si[];
n_si.push("1.0");
n_si.push("3.0");
n_si.push("5.0");

xSizeDef = 6cm;
ySizeDef = 5cm;
yTicksDef = RightTicks(5., 1.);

int gx=0, gy=0;

TF1_nPoints = 4;

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	real rp_eff_cen[] = { 0.98, 0.98, 0.97, 0.98};
	//if (datasets[dsi] == "DS2a")
	//	rp_eff_cen = new real[] { 0.95, 0.98, 0.98, 0.96 };

	for (int dgi : diagonals.keys)
	{
		string f = topDir + datasets[dsi] + "/eff3outof4_"+diagonals[dgi]+".root";
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

		frame fLegend;

		++gy; gx = 0;
		for (int rpi : rps.keys)
		{
			string d = diagonals[dgi] + "/" + rps[rpi];

			++gx;
			NewPad("$\th_y^*\ung{\mu rad}$", "\ung{\%}", gx, gy);
			currentpad.yTicks = RightTicks(1., 0.5);

			for (int nsi : n_si.keys)
			{
				pen p = StdPen(nsi+1);
				draw(scale(1e6, 100), RootGetObject(f, "excluded RPs "+rps[rpi]+"/n_si " + n_si[nsi] + "/th_y dependence/h_simple_ratio.th_y"),
					opt, p, "$n_\si = " + n_si[nsi] + "$");
			}

			limits((0, 100*rp_eff_cen[rpi] - 2), (150, 100*rp_eff_cen[rpi] + 2), Crop);
			fLegend = BuildLegend();
		}

		if (dgi == 0)
		{
			++gx;
			NewPad(false, gx, gy);
			add(fLegend);
		}
	}
}

GShipout("eff3outof4_n_si_cmp", vSkip=0pt);
