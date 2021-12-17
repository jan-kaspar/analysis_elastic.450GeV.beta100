import root;
import pad_layout;
include "../common.asy";

string datasets[] = {
	"data/all-good/Totem1/default"
};

string diagonals[], dgn_labels[];
diagonals.push("45b_56t"); dgn_labels.push("45b -- 56t");
diagonals.push("45t_56b"); dgn_labels.push("45t -- 56b");

real th_min = 40e-6;
real th_max = 140e-6;

//----------------------------------------------------------------------------------------------------

for (int di : datasets.keys)
{
	for (int dgni : diagonals.keys)
	{
		NewRow();

		NewPadLabel("\vbox{\hbox{" + datasets[di] + "}\hbox{" + dgn_labels[dgni] + "}}");

		RootObject h2 = RootGetObject(topDir+datasets[di]+"/distributions_"+diagonals[dgni]+".root", "acceptance correction/h2_th_vs_phi_after");

		int bi_y_min = h2.oExec("GetYaxis").iExec("FindBin", th_min);
		int bi_y_max = h2.oExec("GetYaxis").iExec("FindBin", th_max);

		for (int bi_y = bi_y_min; bi_y <= bi_y_max; ++bi_y)
		{
			real th = h2.oExec("GetYaxis").rExec("GetBinCenter", bi_y);

			NewPad("$\ph^*\ung{\pi}$");

			RootObject h_proj = h2.oExec("ProjectionX", "", bi_y, bi_y);
			draw(scale(1/pi, 1), h_proj, "eb", red);

			real phi_min = 0, phi_max = 1;
			if (diagonals[dgni] == "45b_56t") { phi_min = 0; phi_max = 1; }
			if (diagonals[dgni] == "45t_56b") { phi_min = -1; phi_max = 0; }

			xlimits(phi_min, phi_max, Crop);

			AttachLegend(format("$\th^* \approx %.0f$", th*1e6), S, N);
		}
	}

	NewRow();
}
