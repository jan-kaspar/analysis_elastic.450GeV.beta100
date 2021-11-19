import root;
import pad_layout;
include "../common.asy";


string diagonals[], d_labels[];
diagonals.push("45b_56t"); d_labels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); d_labels.push("45 top -- 56 bot");
diagonals.push("combined"); d_labels.push("combined");

string collections[], c_labels[];
collections.push("merged"); c_labels.push("without horizontals");
collections.push("merged-only-with-hor"); c_labels.push("with horizontals");

drawGridDef = true;

TH1_x_min = t_min;
real t_max_with_hor = 0.009;

string binning = "sb1";

//----------------------------------------------------------------------------------------------------

for (int dgni : diagonals.keys)
	NewPadLabel(d_labels[dgni]);

NewRow();


for (int dgni : diagonals.keys)
{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$", 12cm, 9cm);
	scale(Linear, Log);
	currentpad.xTicks = LeftTicks(0.005, 0.001);

	for (int ci : collections.keys)
	{
		pen p = StdPen(ci + 1);

		draw(RootGetObject(topDir+"data/merged.root", binning + "/" + collections[ci] + "/" + diagonals[dgni] + "/h_dsdt"),
			"d0,eb,vl", p, c_labels[ci]);

		//AddToLegend(format("events $%.2E$", robj.rExec("GetEntries")));
	}
	
	limits((0, 1e2), (0.012, 3e3), Crop);

	yaxis(XEquals(t_min, false), dashed);
	yaxis(XEquals(t_max_with_hor, false), dashed);

	AttachLegend();
}

GShipout(vSkip=0mm);
