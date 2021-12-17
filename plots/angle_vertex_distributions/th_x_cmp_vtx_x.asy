import root;
import pad_layout;
include "../common.asy";

string datasets[];
datasets.push("data/fill7280/Totem1");
datasets.push("data/fill7281/Totem1");
datasets.push("data/fill7291/Totem1");

string dgns[], d_labels[];
dgns.push("45b_56t"); d_labels.push("45 bot -- 56 top");
dgns.push("45t_56b"); d_labels.push("45 top -- 56 bot");

string cuts[], c_labels[];
cuts.push("_low_vtx_x"); c_labels.push("$x^* < -0.4$");
cuts.push("_mid_vtx_x"); c_labels.push("$-0.4 < x^* < +0.4$");
cuts.push("_hig_vtx_x"); c_labels.push("$x^* > +0.4$");

//----------------------------------------------------------------------------------------------------

real GetNormalisation(RootObject hist, real x_min, real x_max)
{
	int bi_min = hist.oExec("GetXaxis").iExec("FindBin", x_min);
	int bi_max = hist.oExec("GetXaxis").iExec("FindBin", x_max);

	real s = 0;
	for (int bi = bi_min; bi <= bi_max; ++bi)
		s += hist.rExec("GetBinContent", bi);

	write(s);

	return s;
}

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int dgni : dgns.keys)
	NewPadLabel(d_labels[dgni]);

for (int dsi : datasets.keys)
{
	NewRow();

	NewPadLabel(datasets[dsi]);

	for (int dgni : dgns.keys)
	{
		string f = topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root";

		NewPad("$\th^*_x\ung{\mu rad}$");

		for (int ci : cuts.keys)
		{
			RootObject hist = RootGetObject(f, "selected - angles/h_th_x" + cuts[ci]);
			real norm = GetNormalisation(hist, -50e-6, +50e-6);

			hist.vExec("Rebin", 4);

			draw(scale(1e6, 1./norm), hist, "vl", StdPen(ci + 1), c_labels[ci]);
		}
	}

	AttachLegend(NW, NE);
}

GShipout(vSkip=0mm);
