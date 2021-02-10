import root;
import pad_layout;
include "../common.asy";

string binnings[] = {
	//"ub",
	"eb",
};

drawGridDef = true;

xSizeDef = 12cm;
ySizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

for (int bi : binnings.keys)
{
	NewRow();

	string binning = binnings[bi];

	NewPad(false);
	label("{\SetFontSizesXX " + binning + "}");

	// ----------

	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	scale(Linear, Log);
	currentpad.xTicks = LeftTicks(0.005, 0.001);

	draw(RootGetObject(topDir+"data/merged.root", binning + "/merged/combined/h_dsdt"), "d0,eb", red);

	limits((0, 4e1), (0.03, 1e4), Crop);
	
	// ----------

	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	currentpad.xTicks = LeftTicks(0.002, 0.001);

	draw(RootGetObject(topDir+"data/merged.root", binning + "/merged/combined/h_dsdt"), "d0,eb", red);

	limits((0, 400), (0.01, 1000), Crop);
}
