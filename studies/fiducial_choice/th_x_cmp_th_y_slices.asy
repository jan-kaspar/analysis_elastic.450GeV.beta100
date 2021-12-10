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

string slices[], s_labels[];
slices.push("30_60"); s_labels.push("$30 \le |\th^*_y| < 60$");
slices.push("60_90"); s_labels.push("$60 \le |\th^*_y| < 90$");
slices.push("90_120"); s_labels.push("$90 \le |\th^*_y| < 120$");
slices.push("120_150"); s_labels.push("$120 \le |\th^*_y| < 150$");

//----------------------------------------------------------------------------------------------------

real GetNormalisation(RootObject hist, real x_min, real x_max)
{
	int bi_min = hist.oExec("GetXaxis").iExec("FindBin", x_min);
	int bi_max = hist.oExec("GetXaxis").iExec("FindBin", x_max);

	write("----------------");
	write(bi_min);
	write(bi_max);

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

for (int sli : slices.keys)
{
	NewRow();

	NewPadLabel(s_labels[sli]);

	for (int dgni : dgns.keys)
	{
		NewPad("$\th^*_x \ung{\mu rad}$");

		for (int dsi : datasets.keys)
		{
			string f = topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root";
			RootObject hist = RootGetObject(f, "selected - angles/h_th_x_th_y_" + slices[sli]);

			real norm = GetNormalisation(hist, -50e-6, +50e-6);

			hist.vExec("Rebin", 5);

			draw(scale(1e6, 1./norm), hist, "vl", StdPen(dsi), replace(datasets[dsi], "_", "\_"));
		}
	}

	AttachLegend(NW, NE);
}
