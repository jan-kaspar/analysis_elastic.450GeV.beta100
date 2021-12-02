import root;
import pad_layout;

string topDir = "../";

string f = topDir + "x_reco_simu.root";

string al_values[];
al_values.push("-0.005");
al_values.push("-0.000");
al_values.push("+0.005");

string be_values[];
be_values.push("-0.050");
be_values.push("+0.000");
be_values.push("+0.020");

//yTicksDef = RightTicks(0.5, 0.1);

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int bei : be_values.keys)
	NewPadLabel("$\be = $" + be_values[bei]);

for (int ali : al_values.keys)
{
	NewRow();

	NewPadLabel("$\al = $" + al_values[ali]);

	for (int bei : be_values.keys)
	{
		NewPad("$x^*\ung{mm}$", "$\th^*_x\ung{\mu rad}$");

		draw(scale(1., 1e6), RootGetObject(f, "al=" + al_values[ali] + ",be=" + be_values[bei] + "/h2_th_x_vs_vtx_x"));
	}
}
