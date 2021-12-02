import root;
import pad_layout;

string topDir = "../";

string f = topDir + "analyze_tilts.root";

string dir = "fill7291/45b_56t/x/R/central/slices";

string objects[] = RootGetListOfObjects(f, dir);

for (int oi = 0; oi < objects.length; oi += 3)
{
	if (oi % 4 == 0)
		NewRow();

	NewPad("$\th_x^*\ung{\mu rad}$");
	string base = dir + "/" + objects[oi];
	draw(scale(1e6, 1), RootGetObject(f, base), "vl", blue);
	draw(scale(1e6, 1), RootGetObject(f, base + "|ff"), "l", red);

	AttachLegend(BuildLegend(replace(objects[oi], "x=", "$x^*=$"), S), N);
}
