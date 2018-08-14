import root;
import pad_layout;
include "../run_info.asy";

string datasets[], d_labels[];
datasets.push("DS1"); d_labels.push("DS1");
datasets.push("DS1-y-cut"); d_labels.push("DS1");
//datasets.push("DS2-y-cut"); d_labels.push("DS2");
//datasets.push("DS3-y-cut"); d_labels.push("DS3");
//datasets.push("DS1"); d_labels.push("DS1");

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };

string types[], t_labels[];
pen t_pens[];
types.push("dgn"); t_labels.push("diagonal"); t_pens.push(red);
types.push("sel"); t_labels.push("selected"); t_pens.push(blue);

string topDir = "../../";

xSizeDef = 10cm;
ySizeDef = 6cm;

//xTicksDef = LeftTicks(1., 0.5);

TGraph_errorBar = None;

int rebin = 10;

transform swToMinutes = shift(-1010, 0) * scale(1/60, 1);

//----------------------------------------------------------------------------------------------------

void SetPadWidth()
{
	/*
	real factorHoursToSize = 50cm / 3;
	real timespan = currentpicture.userMax2().x - currentpicture.userMin2().x;
	currentpad.xSize = timespan * factorHoursToSize;
	*/

	currentpad.xSize = 12cm;
}

//----------------------------------------------------------------------------------------------------

NewPad();

for (int dgni : diagonals.keys)
{
	NewPad(false);
	label("{\SetFontSizesXX " + dgn_labels[dgni] + "}");
}

for (int dsi : datasets.keys)
{
	NewRow();
	
	NewPad(false);
	label("{\SetFontSizesXX " + datasets[dsi] + "}");

	for (int dgni : diagonals.keys)
	{
		NewPad("time $\ung{min}$", "rate$\ung{Hz}$");
		//currentpad.yTicks = RightTicks(1., 0.2);
		real y_min = 0, y_max = 20;

		if (datasets[dsi] == "DS1" && diagonals[dgni] == "45b_56t")
			y_max = 200.;
	
		//DrawRunBands(fills[dsi], y_min, y_max);

		for (int ti : types.keys)
		{
			RootObject hist = RootGetObject(topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root", "metadata/rate cmp|h_timestamp_" + types[ti]);
			hist.vExec("Rebin", rebin);

			draw(scale(1., 1./rebin) * swToMinutes, hist, "vl", t_pens[ti]);
		}

		ylimits(y_min, y_max, Crop);
		SetPadWidth();
	}
}

/*
NewPad(false);
for (int dgni : diagonals.keys)
{
	AddToLegend(dgn_labels[dgni], dgn_pens[dgni]);
}
AttachLegend();

*/

GShipout(vSkip=0mm);
