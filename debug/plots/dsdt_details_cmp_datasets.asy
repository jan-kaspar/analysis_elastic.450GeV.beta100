import root;
import pad_layout;

string topDir = "../../";

string f = topDir + "data/merged.root";

string datasets[] = {
	"fill7280",
	"fill7282",
	"fill7284",
	"fill7289",
	"fill7291",
};

string diagonal = "combined";

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	draw(RootGetObject(f, "sb1/" + datasets[dsi] + "/" + diagonal + "/h_dsdt"), "vl,eb", StdPen(dsi));

	real x = 0.0018;
	draw((x, 220)--(x, 270), black+1pt);

	real x = 0.0027;
	draw((x, 190)--(x, 240), black+1pt);

	limits((0, 100), (0.004, 500), Crop);
	AttachLegend(datasets[dsi]);
}

//----------------------------------------------------------------------------------------------------
NewRow();

NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");

for (int dsi : datasets.keys)
{
	draw(RootGetObject(f, "sb1/" + datasets[dsi] + "/" + diagonal + "/h_dsdt"), "vl,eb", StdPen(dsi));
}

	real x = 0.0018;
	draw((x, 220)--(x, 270), black+1pt);

	real x = 0.0027;
	draw((x, 190)--(x, 240), black+1pt);

limits((0, 100), (0.004, 500), Crop);
AttachLegend("overlapped");

GShipout(hSkip = 0mm);
