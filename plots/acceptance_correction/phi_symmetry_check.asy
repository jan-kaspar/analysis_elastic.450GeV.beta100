import root;
import pad_layout;
include "../common.asy";

string datasets[] = {
	"data/all-good/Totem1/default"
};

string diagonals[], dgn_labels[];
diagonals.push("45b_56t"); dgn_labels.push("45b -- 56t");
diagonals.push("45t_56b"); dgn_labels.push("45t -- 56b");

real th_x_signs[];
string th_x_labels[];
th_x_signs.push(+1); th_x_labels.push("positive $\th^*_x$");
th_x_signs.push(-1); th_x_labels.push("negative $\th^*_x$");

int rebin = 4;

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int ti : th_x_signs.keys)
	NewPadLabel(th_x_labels[ti]);

for (int di : datasets.keys)
{
	for (int dgni : diagonals.keys)
	{
		NewRow();

		NewPadLabel("\vbox{\hbox{" + datasets[di] + "}\hbox{" + dgn_labels[dgni] + "}}");

		RootObject h_th_x = RootGetObject(topDir+datasets[di]+"/distributions_"+diagonals[dgni]+".root", "selected - angles/h_th_x_sym_cmp");
		h_th_x.vExec("Rebin", rebin);

		RootObject h_th_y = RootGetObject(topDir+datasets[di]+"/distributions_"+diagonals[dgni]+".root", "selected - angles/h_th_y_sym_cmp");
		h_th_y.vExec("Rebin", rebin);

		for (int ti : th_x_signs.keys)
		{
			NewPad("$\th^*_{x,y}\ung{\mu rad}$");

			draw(scale(1e6 * th_x_signs[ti], 1.), h_th_x, "d0,eb", blue, "$\th^*_x$");
			draw(scale(1e6, 0.5), h_th_y, "d0,eb", red, "$\th^*_y$");

			if (diagonals[dgni] == "45b_56t")
				xlimits(30, 130, Crop);
			if (diagonals[dgni] == "45t_56b")
				xlimits(-130, -30, Crop);
		}

		AttachLegend(NW, NE);
	}

	NewRow();
}

GShipout(vSkip = 0mm);
