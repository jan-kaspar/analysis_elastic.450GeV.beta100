import root;
import pad_layout;
include "../common.asy";

string topDir = "../../";

string diagonals[] = { "45t_56b" };
string diagonal_labels[] = { "45t -- 56b" };

string models[] = {
	"fit-1",
};

string dataset = "DS-fill7291/Totem1";

xSizeDef = 10cm;
ySizeDef = 8cm;

TGraph_x_min = t_min;

//----------------------------------------------------------------------------------------------------

for (int dgni : diagonals.keys)
{
	NewRow();

	NewPad(false);
	label("\vbox{\SetFontSizesXX\hbox{" + dataset + "}\hbox{" + diagonal_labels[dgni] + "}}");


	// ----- full t range -----

	NewPad("$|t|\ung{GeV^2}$", "mutiplicative correction");
	//currentpad.yTicks = RightTicks(0.005, 0.001);

	for (int mi : models.keys)
	{
		string f = topDir + dataset + "/unfolding_cf_ni_" + diagonals[dgni] + ".root";
		draw(RootGetObject(f, models[mi] + "/g_t_corr"), StdPen(mi+1), replace(models[mi], "_", "\_"));
	}

	limits((0, 0.90), (0.05, 1.30), Crop);

	AttachLegend(SE, SE);


	// ----- low |t| zoom -----

	/*
	NewPad("$|t|\ung{GeV^2}$", "mutiplicative correction");
	currentpad.xTicks = LeftTicks(0.0005, 0.0001);
	currentpad.yTicks = RightTicks(0.005, 0.001);

	for (int mi : models.keys)
	{
		string f = topDir + dataset + "/unfolding_cf_ni_" + diagonals[dgni] + ".root";
		draw(RootGetObject(f, models[mi] + "/g_t_corr"), StdPen(mi), replace(models[mi], "_", "\_"));
	}

	limits((0.0005, 0.995), (0.003, 1.005), Crop);

	yaxis(XEquals(t_min, false), dashed);
	*/

	AttachLegend(SE, SE);
}

GShipout(margin=1mm);
