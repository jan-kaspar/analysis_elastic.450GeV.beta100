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
datasets.push("merged");

string diagonal = "combined";

string binning = "sb1";

drawGridDef = true;

xSizeDef = 16cm;
ySizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
scale(Linear, Log);

for (int dsi : datasets.keys)
{
	pen p = (datasets[dsi] == "merged") ? black : StdPen(dsi + 1);
	draw(RootGetObject(topDir+"data/merged.root", binning + "/" + datasets[dsi] + "/" + diagonal + "/h_dsdt"), "d0,vl,eb", p, datasets[dsi]);
}

limits((0, 4e1), (0.03, 1e4), Crop);

AttachLegend();
