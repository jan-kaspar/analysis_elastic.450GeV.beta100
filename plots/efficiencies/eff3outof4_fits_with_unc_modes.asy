import root;
import pad_layout;
include "../common.asy";

string datasets[], fills[];
/*
datasets.push("data/fill7280/Totem1"); fills.push("7280");
datasets.push("data/fill7281/Totem1"); fills.push("7281");
datasets.push("data/fill7282/Totem1"); fills.push("7282");
datasets.push("data/fill7283/Totem1"); fills.push("7283");
datasets.push("data/fill7284/Totem1"); fills.push("7284");
datasets.push("data/fill7285/Totem1"); fills.push("7285");
//datasets.push("data-bad/fill7286/Totem1"); fills.push("7286");
//datasets.push("data-bad/fill7287/Totem1"); fills.push("7287");
//datasets.push("data-bad/fill7288/Totem1"); fills.push("7288");
datasets.push("data/fill7289/Totem1"); fills.push("7289");
//datasets.push("data-bad/fill7290/Totem1"); fills.push("7290");
*/
datasets.push("data/fill7291/Totem1"); fills.push("7291");

string diagonals[];
diagonals.push("45b_56t");
//diagonals.push("45t_56b");

string rps[], rp_labels[];
rps.push("L_2_F"); rp_labels.push("45-220-fr");
rps.push("L_1_F"); rp_labels.push("45-210-fr");
rps.push("R_1_F"); rp_labels.push("56-210-fr");
rps.push("R_2_F"); rp_labels.push("56-220-fr" );

string slices[], s_labels[];
slices.push("slice_th_x_-250_-200"); s_labels.push("$-250 < \th^*_x < -200\un{\mu rad}$");
//slices.push("slice_th_x_-200_-100"); s_labels.push("$-200 < \th^*_x < -100\un{\mu rad}$");
slices.push("slice_th_x_-100_+0"); s_labels.push("$-100 < \th^*_x < 0\un{\mu rad}$");
//slices.push("slice_th_x_+0_+100"); s_labels.push("$0 < \th^*_x < +100\un{\mu rad}$");
//slices.push("slice_th_x_+100_+200"); s_labels.push("$+100 < \th^*_x < +200\un{\mu rad}$");
//slices.push("slice_th_x_+200_+250"); s_labels.push("$+200 < \th^*_x < +250\un{\mu rad}$");

xSizeDef = 6cm;
ySizeDef = 5cm;
yTicksDef = RightTicks(5., 1.);

//----------------------------------------------------------------------------------------------------

void DrawModes(RootObject g_fit)
{
	g_fit.Print();

	for (int m = 0; m < 2; ++m)
	{
		guide g;

		for (int p = 0; p < g_fit.iExec("GetN"); ++p)
		{
			real ax[] = {0.};
			real ay[] = {0.};
			g_fit.vExec("GetPoint", p, ax, ay);

			real th_y = ax[0];
			real eff = ay[0];

			real corr = 0.;

			if (m == 0) corr = +0.02;
			if (m == 1) corr = +0.02 - 0.04 * th_y / 150e-6;

			g = g -- (th_y * 1e6, (eff + corr) * 100);
		}

		draw(g, StdPen(m + 3) + dashed);
	}
}

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	real rp_eff_cen[] = { 0.96, 0.98, 0.97, 0.98};

	for (int dgi : diagonals.keys)
	{
		NewPage();

		string f = topDir + datasets[dsi] + "/eff3outof4_fit_" + diagonals[dgi] + ".root";

		NewRow();

		NewPadLabel(replace("\vbox{\SetFontSizesXX\hbox{dataset: "+datasets[dsi]+"}\hbox{diagonal: "+diagonals[dgi]+"}}", "_", "\_"));
		
		for (int rpi : rps.keys)
			NewPadLabel(rp_labels[rpi]);
		
		frame fLegend;

		for (int sli : slices.keys)
		{
			NewRow();

			NewPadLabel(s_labels[sli]);

			for (int rpi : rps.keys)
			{
				NewPad("$\th_y^*\ung{\mu rad}$", "\ung{\%}");
				currentpad.yTicks = RightTicks(1., 0.5);

				string p_base = rps[rpi] + "/" + slices[sli] + "/cmp";

				draw(scale(1e6, 100), RootGetObject(f, p_base+"|h_th_y_slice"), "vl,eb", blue, "efficiency histogram");

				RootObject g_fit = RootGetObject(f, p_base+"|g_fit");
				draw(scale(1e6, 100), g_fit, "l", red, "fit");

				DrawModes(g_fit);

				//limits((0, 100*rp_eff_cen[rpi] - 2), (150, 100*rp_eff_cen[rpi] + 2), Crop);
				limits((0, 90), (150, 102), Crop);
				fLegend = BuildLegend();
			}
		}
	}
}

GShipout(vSkip=0pt);
