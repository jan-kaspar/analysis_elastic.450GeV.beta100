import root;
import pad_layout;
include "../common.asy";

string datasets[] = {
	"data/all-good/Totem1/default"
};

string diagonals[], dgn_labels[];
diagonals.push("45b_56t"); dgn_labels.push("45b -- 56t");
diagonals.push("45t_56b"); dgn_labels.push("45t -- 56b");

TH2_palette = new pen[] { paleblue, blue, cyan, heavygreen, yellow, orange, red, magenta, black };
//TH2_palette = Gradient(blue, heavygreen, yellow, red);

TH2_z_min = 1e2;
TH2_z_max = 2.5e3;

//----------------------------------------------------------------------------------------------------

for (int di : datasets.keys)
{
	for (int dgni : diagonals.keys)
	{
		NewPad("$\ph^*\ung{\pi}$", "$\th^*\ung{\mu rad}$");
		TH2_zLabel = "events per bin";
		//scale(Linear, Linear, Log);
		draw(scale(1/pi, 1e6), RootGetObject(topDir+datasets[di]+"/distributions_"+diagonals[dgni]+".root", "acceptance correction/h2_th_vs_phi_after"), "p,bar");

		if (diagonals[dgni] == "45b_56t")
			limits((0, 0), (1, 400), Crop);
		if (diagonals[dgni] == "45t_56b")
			limits((-1, 0), (0, 400), Crop);

		AttachLegend(replace(datasets[di]+", "+dgn_labels[dgni], "_", "\_"), N, N);
	}

	NewRow();
}
