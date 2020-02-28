import root;
import pad_layout;

string top_dir = "../../";

string datasets[] = {
	//"DS-fill7281/Totem1",
	//"DS-fill7289/Totem1",
	"DS-fill7291/Totem1",
};

string diagonals[], diagonal_labels[];
diagonals.push("45b_56t"); diagonal_labels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); diagonal_labels.push("45 top -- 56 bot");

TH2_palette = Gradient(blue, heavygreen, yellow, red);

xSizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	for (int dgni : diagonals.keys)
	{
		NewRow();

		NewPad(false);
		label("\vbox{\SetFontSizesXX\hbox{" + datasets[dsi] + "}\hbox{" + diagonal_labels[dgni]+ "}}");

		string f = top_dir+"/"+datasets[dsi]+"/distributions_" + diagonals[dgni] + ".root";

		//TH2_x_min = -100e-6;
		//TH2_x_max = +100e-6;
		TH2_x_min = -450e-6;
		TH2_x_max = +450e-6;

		if (diagonals[dgni] == "45b_56t")
		{
			TH2_y_min = +30e-6;
			TH2_y_max = +150e-6;
		} else {
			TH2_y_min = -150e-6;
			TH2_y_max = -30e-6;
		}

		//yTicksDef = RightTicks(1., 0.5);
		xTicksDef = LeftTicks(100., 50.);

		// ----- left arm -----

		NewPad("$\th_x^{*}\ung{\mu rad}$", "$\th_y^{*}\ung{\mu rad}$", axesAbove=true);
		scale(Linear, Linear, Log);
		draw(scale(1e6, 1e6), RootGetObject(f, "selected - angles/h2_th_y_L_vs_th_x_L"), "def");

		draw(scale(1e6, 1e6), RootGetObject(f, "fiducial cuts/fc_L_l"), "l", black+1pt);
		draw(scale(1e6, 1e6), RootGetObject(f, "fiducial cuts/fc_L_h"), "l", magenta+1pt);

		limits((TH2_x_min*1e6, TH2_y_min*1e6), (TH2_x_max*1e6, TH2_y_max*1e6), Crop);
		AttachLegend(BuildLegend("left arm", S), N);

		// ----- right arm -----

		NewPad("$\th_x^{*}\ung{\mu rad}$", "$\th_y^{*}\ung{\mu rad}$", axesAbove=true);
		scale(Linear, Linear, Log);
		draw(scale(1e6, 1e6), RootGetObject(f, "selected - angles/h2_th_y_R_vs_th_x_R"), "def");

		draw(scale(1e6, 1e6), RootGetObject(f, "fiducial cuts/fc_R_l"), "l", black+2pt);
		draw(scale(1e6, 1e6), RootGetObject(f, "fiducial cuts/fc_R_h"), "l", magenta+2pt);

		limits((TH2_x_min*1e6, TH2_y_min*1e6), (TH2_x_max*1e6, TH2_y_max*1e6), Crop);
		AttachLegend(BuildLegend("right arm", S), N);

		// ----- both arms -----

		NewPad("$\th_x^{*}\ung{\mu rad}$", "$\th_y^{*}\ung{\mu rad}$", axesAbove=true);
		scale(Linear, Linear, Log);
		draw(scale(1e6, 1e6), RootGetObject(f, "selected - angles/h2_th_y_vs_th_x"), "def");

		draw(scale(1e6, 1e6), RootGetObject(f, "fiducial cuts/fc_G_l"), "l", black+2pt);
		draw(scale(1e6, 1e6), RootGetObject(f, "fiducial cuts/fc_G_h"), "l", magenta+2pt);

		limits((TH2_x_min*1e6, TH2_y_min*1e6), (TH2_x_max*1e6, TH2_y_max*1e6), Crop);
		AttachLegend(BuildLegend("two-arm", S), N);
	}
}

GShipout(margin=1mm, hSkip=1mm);
