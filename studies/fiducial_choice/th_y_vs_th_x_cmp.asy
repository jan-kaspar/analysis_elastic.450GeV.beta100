import root;
import pad_layout;

string topDir = "../../data/all-good-tune/Totem1/";

string datasets[];
datasets.push("default");
datasets.push("vtx_x_low");
datasets.push("vtx_x_mid");
datasets.push("vtx_x_hig");

string dgns[], d_labels[];
dgns.push("45b_56t"); d_labels.push("45 bot -- 56 top");
dgns.push("45t_56b"); d_labels.push("45 top -- 56 bot");

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int dgni : dgns.keys)
	NewPadLabel(d_labels[dgni]);

for (int dsi : datasets.keys)
{
	NewRow();

	NewPadLabel(replace(datasets[dsi], "_", "\_"));

	for (int dgni : dgns.keys)
	{
		NewPad("$\th^*_x\ung{\mu rad}$", "$\th^*_y\ung{\mu rad}$");
		scale(Linear, Linear, Log);

		string f = topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root";
		RootObject h2 = RootGetObject(f, "selected - angles/h2_th_y_G_vs_th_x_G");

		draw(scale(1e6, 1e6), h2);
	}
}
