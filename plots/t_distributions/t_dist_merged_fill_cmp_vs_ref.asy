import root;
import pad_layout;
include "../common.asy";

string datasets[];
datasets.push("fill7280");
datasets.push("fill7281");
datasets.push("fill7282");
datasets.push("fill7283");
datasets.push("fill7284");
datasets.push("fill7285");
datasets.push("fill7289");
datasets.push("fill7291");

string dataset_ref = "merged";
string diagonal_ref = "combined";

string diagonals[], d_labels[];
pen d_pens[];
diagonals.push("45b_56t"); d_labels.push("45 bot -- 56 top"); d_pens.push(blue);
diagonals.push("45t_56b"); d_labels.push("45 top -- 56 bot"); d_pens.push(red);

string binning = "sb1";

drawGridDef = true;

//xSizeDef = 16cm;
//ySizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

string f = topDir+"data/merged.root";

RootObject h_ref = RootGetObject(f, binning + "/" + dataset_ref + "/" + diagonal_ref + "/h_dsdt");

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	scale(Linear, Log);

	for (int dgni : diagonals.keys)
	{
		draw(RootGetObject(f, binning + "/" + datasets[dsi] + "/" + diagonals[dgni] + "/h_dsdt"), "d0,eb", d_pens[dgni], d_labels[dgni]);
	}

	draw(h_ref, "d0,vl", black, "ref (" + dataset_ref + ", " + diagonal_ref + ")");

	limits((0, 4e1), (0.03, 1e4), Crop);

	AttachLegend(datasets[dsi]);
}

GShipout(hSkip = 0mm);
