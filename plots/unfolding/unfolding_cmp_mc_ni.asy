import root;
import pad_layout;
include "../common.asy";

string datasets[] = {
	"data/fill7291/Totem1"
};

string diagonals[] = { "45b_56t", "45t_56b" };
string diagonal_labels[] = { "45b -- 56t", "45t -- 56b" };

string model = "fit-1";

string binning = "eb";

//xSizeDef = 5.1cm;
//ySizeDef = 5.1cm;

real y_min = 0.90, y_max = 1.30;

TGraph_x_min = t_min;
TH1_x_min = t_min;

//----------------------------------------------------------------------------------------------------

for (string dataset : datasets)
{
	NewPad();

	for (int dgni : diagonals.keys)
	{
		NewRow();

		NewPad(false);
		label("\vbox{\SetFontSizesXX\hbox{" + dataset + "}\hbox{" + diagonal_labels[dgni] + "}}");

		string f_ni = topDir + dataset + "/unfolding_cf_ni_" + diagonals[dgni] + ".root";
		string f_mc = topDir + dataset + "/unfolding_cf_mc_" + diagonals[dgni] + ".root";


		// ----- full |t| range -----

		NewPad("$|t|\ung{GeV^2}$", "mutiplicative correction");

		draw(RootGetObject(f_mc, model + "/" + binning + "/h_corr"), "eb", blue);

		draw(RootGetObject(f_ni, model + "/g_t_corr"), red);

		limits((0, y_min), (0.05, y_max), Crop);


		// ----- low |t| zoom -----

		NewPad("$|t|\ung{GeV^2}$", "mutiplicative correction");
		currentpad.xTicks = LeftTicks(1e-3, 5e-4);

		draw(RootGetObject(f_mc, model + "/" + binning + "/h_corr"), "eb,vl", blue, "Monte Carlo");

		draw(RootGetObject(f_ni, model + "/g_t_corr"), red, "numerical integration");

		limits((0, y_min), (0.005, y_max), Crop);

		yaxis(XEquals(t_min, false), dashed);

		AttachLegend(dataset + ", " + diagonal_labels[dgni], NW, NE);
	}
}

GShipout(margin=1mm);
