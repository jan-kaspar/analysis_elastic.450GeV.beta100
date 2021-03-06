import root;
import pad_layout;
include "../common.asy";

string datasets[] = {
	"data/fill7291/Totem1"
};

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };


TH2_palette = new pen[] { paleblue, blue, cyan, heavygreen, yellow, orange, red, magenta, black };
//TH2_palette = Gradient(blue, heavygreen, yellow, red);

TH2_z_min = 1e2;
TH2_z_max = 7e2;

for (int di : datasets.keys)
{
	for (int dgni : diagonals.keys)
	{
		NewPad("$\ph$", "$\th^*\ung{\mu rad}$");
		TH2_zLabel = "events per bin";
		//scale(Linear, Linear, Log);
		draw(scale(1, 1e6), RootGetObject(topDir+datasets[di]+"/distributions_"+diagonals[dgni]+".root", "acceptance correction/h2_th_vs_phi_after"), "p,bar");
		ylimits(0, 400, Crop);
		AttachLegend(replace(datasets[di]+", "+dgn_labels[dgni], "_", "\_"), N, N);
	}

	NewRow();
}
