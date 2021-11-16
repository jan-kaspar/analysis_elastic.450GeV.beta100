include "shared.asy";

string selections[], s_labels[];
selections.push("_low_th_x"); s_labels.push("$\th_x^* < -250\un{\mu rad}$");
selections.push("_mid_th_x"); s_labels.push("$-250 < \th_x^* < +250\un{\mu rad}$");
selections.push("_hig_th_x"); s_labels.push("$\th_x^* > +250\un{\mu rad}$");

//----------------------------------------------------------------------------------------------------

NewPad(false);

for (int si : selections.keys)
	NewPadLabel(s_labels[si]);

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	for (int dgni : dgns.keys)
	{
		NewRow();

		NewPadLabel("\vbox{\hbox{" + datasets[dsi] + "}\hbox{" + d_labels[dgni] + "}}");

		for (int si : selections.keys)
		{
			NewPad("$\th^{*,R}_x\ung{\mu rad}$", "$\th^{*,L}_x\ung{\mu rad}$");

			RootObject h2 = RootGetObject(topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root", "selected - angles/h2_th_y_L_vs_th_y_R" + selections[si]);

			if (rebin)
				h2.vExec("Rebin2D", 2, 2);

			draw(scale(1e6, 1e6), h2);

			if (dgns[dgni] == "45b_56t")
			{
				draw((0, -0)--(+150, +150), magenta+1pt);
				limits((0, -0), (+150, +150), Crop);
			}

			if (dgns[dgni] == "45t_56b")
			{
				draw((-150, -150)--(0, 0), magenta+1pt);
				limits((-150, -150), (0, 0), Crop);
			}
		}
	}
}

GShipout(vSkip=0mm);
