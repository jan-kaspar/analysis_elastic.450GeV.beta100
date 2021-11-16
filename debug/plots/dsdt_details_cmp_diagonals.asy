import root;
import pad_layout;

string topDir = "../../";

string f = topDir + "data/merged.root";

string dataset = "merged";

string diagonals[] = {
	"45b_56t",
	"45t_56b",
};

//----------------------------------------------------------------------------------------------------

for (int dgni : diagonals.keys)
{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	draw(RootGetObject(f, "sb1/" + dataset + "/" + diagonals[dgni] + "/h_dsdt"), "vl,eb", StdPen(dgni));

	real x = 0.0018;
	draw((x, 220)--(x, 270), black+1pt);

	real x = 0.0027;
	draw((x, 190)--(x, 240), black+1pt);

	limits((0, 100), (0.004, 500), Crop);
	AttachLegend(replace(diagonals[dgni], "_", "-"));
}

//----------------------------------------------------------------------------------------------------
NewRow();

NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");

for (int dgni : diagonals.keys)
{
	draw(RootGetObject(f, "sb1/" + dataset + "/" + diagonals[dgni] + "/h_dsdt"), "vl,eb", StdPen(dgni));
}

	real x = 0.0018;
	draw((x, 220)--(x, 270), black+1pt);

	real x = 0.0027;
	draw((x, 190)--(x, 240), black+1pt);

limits((0, 100), (0.004, 500), Crop);
AttachLegend("overlapped");
