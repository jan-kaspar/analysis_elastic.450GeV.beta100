import root;
import pad_layout;

include "../common.asy";

string topDir = "../../";

string diagonals[], diagLabels[];
diagonals.push("45b_56t"); diagLabels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); diagLabels.push("45 top -- 56 bot");

drawGridDef = true;

TH1_x_min = t_min;

string binning = "eb";

//----------------------------------------------------------------------------------------------------

NewPad("$|t|\ung{GeV^2}$", "$\d N/\d t\ung{mb/GeV^2}$", 12cm, 9cm);
scale(Linear, Log);
	currentpad.xTicks = LeftTicks(0.005, 0.001);

for (int dgni : diagonals.keys)
{
	pen p = StdPen(dgni + 1);

	draw(RootGetObject(topDir+"DS-merged/merged.root", binning + "/merged/" + diagonals[dgni] + "/h_dsdt"), "d0,eb,vl", p, diagLabels[dgni]);

	AddToLegend(format("events $%.2E$", robj.rExec("GetEntries")));
}

//currentpad.xTicks = LeftTicks(0.002, 0.001);
//currentpad.yTicks = RightTicks(100., 50.);
limits((0, 4e1), (0.03, 1e4), Crop);

yaxis(XEquals(2e-4, false), dashed);

AttachLegend();
