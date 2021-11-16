include "shared.asy";

string selections[], s_labels[];
selections.push("_low_vtx_x"); s_labels.push("$x^* < -0.7\un{mm}$");
selections.push("_mid_vtx_x"); s_labels.push("$-0.7 < x^* < +0.7\un{mm}$");
selections.push("_hig_vtx_x"); s_labels.push("$x^* > +0.7\un{mm}$");

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

			RootObject h2 = RootGetObject(topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root", "selected - angles/h2_th_x_L_vs_th_x_R" + selections[si]);

			if (rebin)
				h2.vExec("Rebin2D", 2, 2);

			draw(scale(1e6, 1e6), h2);

			draw((-450, -450)--(+450, +450), magenta+1pt);
			limits((-450, -450), (+450, +450), Crop);
		}
	}
}

GShipout(vSkip=0mm);
