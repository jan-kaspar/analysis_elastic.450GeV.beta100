import root;
import pad_layout;
include "../common.asy";

string diagonals[] = { "45t_56b" };
string diagonal_labels[] = { "45t -- 56b" };

string model = "fit-1";

string dataset = "data/fill7291/Totem1";

string binnings[] = {
	"eb",
};

xSizeDef = 10cm;
ySizeDef = 8cm;

TGraph_x_min = t_min;
TH1_x_min = t_min;

//----------------------------------------------------------------------------------------------------

void PlotAll(string f)
{
	draw(RootGetObject(f, model + "/g_t_corr"), black+1pt, "graph");

	for (int bi : binnings.keys)
	{
		draw(RootGetObject(f, model + "/" + binnings[bi]), "vl", StdPen(bi+1), binnings[bi]);
	}
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

for (int dgni : diagonals.keys)
{
	NewRow();

	NewPad(false);
	label("\vbox{\SetFontSizesXX\hbox{" + dataset + "}\hbox{" + diagonal_labels[dgni] + "}}");

	string f = topDir + dataset + "/unfolding_cf_ni_" + diagonals[dgni] + ".root";

	// ----- full t range -----

	NewPad("$|t|\ung{GeV^2}$", "mutiplicative correction");
	//currentpad.yTicks = RightTicks(0.001, 0.0005);

	PlotAll(f);

	limits((0, 0.9), (0.005, 1.30), Crop);

	AttachLegend(SE, SE);


	// ----- low |t| zoom -----

	/*
	NewPad("$|t|\ung{GeV^2}$", "mutiplicative correction");
	currentpad.xTicks = LeftTicks(0.0005, 0.0001);
	currentpad.yTicks = RightTicks(0.001, 0.0005);
	
	PlotAll(f);

	limits((0.0005, 0.995), (0.003, 1.001), Crop);

	yaxis(XEquals(t_min, false), dashed);

	AttachLegend(SE, SE);
	*/
}

GShipout(margin=1mm);
