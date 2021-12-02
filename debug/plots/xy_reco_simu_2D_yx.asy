import root;
import pad_layout;

string topDir = "../";

string f = topDir + "xy_reco_simu.root";

string sym_values[];
sym_values.push("+0.000");
sym_values.push("+2000.000");
sym_values.push("+4000.000");

string asym_values[];
asym_values.push("+0.000");
asym_values.push("+2000.000");
asym_values.push("+4000.000");

//yTicksDef = RightTicks(0.5, 0.1);

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int bei : asym_values.keys)
{
	NewPadLabel("asym:" + asym_values[bei]);
	NewPad(false);
}

for (int ali : sym_values.keys)
{
	NewRow();

	NewPadLabel("sym:" + sym_values[ali]);

	for (int bei : asym_values.keys)
	{
		string dir = "+0.000,+0.000," + sym_values[ali] + "," + asym_values[bei];

		NewPad("$\th^*_y\ung{\mu rad}$", "$\De^{R-L}\th_x^*\ung{\mu rad}$");
		draw(scale(1e6, 1e6), RootGetObject(f, dir + "/h2_th_x_RLdiff_vs_th_y"));

		NewPad("$\th^*_x\ung{\mu rad}$", "$\De^{R-L}\th_y^*\ung{\mu rad}$");
		draw(scale(1e6, 1e6), RootGetObject(f, dir + "/h2_th_y_RLdiff_vs_th_x"));
	}
}
