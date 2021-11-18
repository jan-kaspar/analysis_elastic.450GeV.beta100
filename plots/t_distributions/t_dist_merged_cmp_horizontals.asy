import root;
import pad_layout;
include "../common.asy";

string fills[];
fills.push("7281");
fills.push("7289");
fills.push("7291");

string diagonals[], d_labels[];
diagonals.push("45b_56t"); d_labels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); d_labels.push("45 top -- 56 bot");

string v_tags[], v_labels[];
v_tags.push(""); v_labels.push("without horizontals");
v_tags.push("-with-hor"); v_labels.push("with horizontals");

drawGridDef = true;

TH1_x_min = t_min;
real t_max_with_hor = 0.009;

string binning = "sb1";

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int dgni : diagonals.keys)
	NewPadLabel(d_labels[dgni]);

for (int fi : fills.keys)
{
	NewRow();

	NewPadLabel(fills[fi]);

	for (int dgni : diagonals.keys)
	{
		NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$", 12cm, 9cm);
		scale(Linear, Log);
		currentpad.xTicks = LeftTicks(0.005, 0.001);

		for (int vi : v_tags.keys)
		{
			pen p = StdPen(vi + 1);

			string ds = "fill" + fills[fi] + v_tags[vi];

			draw(RootGetObject(topDir+"data/merged.root", binning + "/" + ds + "/" + diagonals[dgni] + "/h_dsdt"),
				"d0,eb,vl", p, v_labels[vi]);

			//AddToLegend(format("events $%.2E$", robj.rExec("GetEntries")));
		}
		
		limits((0, 4e1), (0.012, 1e4), Crop);
		//limits((0, 4e1), (0.003, 1e4), Crop);

		yaxis(XEquals(t_min, false), dashed);
		yaxis(XEquals(t_max_with_hor, false), dashed);

		AttachLegend();
	}
}

GShipout(vSkip=0mm);
