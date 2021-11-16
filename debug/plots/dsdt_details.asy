import root;
import pad_layout;

string topDir = "../../";

string f = topDir + "data/merged.root";

string dataset = "merged";
string diagonal = "combined";

//----------------------------------------------------------------------------------------------------

{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	draw(RootGetObject(f, "sb1/" + dataset + "/" + diagonal + "/h_dsdt"), "vl,eb", red);

	real x = 0.0018;
	draw((x, 220)--(x, 270), black+1pt);

	real x = 0.0027;
	draw((x, 190)--(x, 240), black+1pt);

	limits((0, 100), (0.004, 500), Crop);
}
