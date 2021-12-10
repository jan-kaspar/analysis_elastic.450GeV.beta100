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

string q_tags[], q_labels[], q_types[];
q_tags.push("h_th_x"); q_labels.push("\th^*_x"); q_types.push("x");
//q_tags.push("h_th_x_L"); q_labels.push("\th^{*L}_x"); q_types.push("x");
//q_tags.push("h_th_x_R"); q_labels.push("\th^{*R}_x"); q_types.push("x");

q_tags.push("h_th_y"); q_labels.push("\th^*_y"); q_types.push("y");
//q_tags.push("h_th_y_L"); q_labels.push("\th^{*L}_y"); q_types.push("y");
//q_tags.push("h_th_y_R"); q_labels.push("\th^{*R}_y"); q_types.push("y");

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

for (int qi : q_tags.keys)
{
	NewRow();

	NewPadLabel("$" + q_labels[qi] + "$");

	for (int dgni : dgns.keys)
	{
		NewPad("$" + q_labels[qi] + "\ung{\mu rad}$");

		for (int dsi : datasets.keys)
		{
			string f = topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root";
			RootObject hist = RootGetObject(f, "selected - angles/" + q_tags[qi]);

			real norm = 1.;

			if (q_types[qi] == "x")
				norm = GetNormalisation(hist, -50e-6, +50e-6);

			if (q_types[qi] == "y")
			{
				if (dgns[dgni] == "45b_56t")
					norm = GetNormalisation(hist, +60e-6, +120e-6);
				if (dgns[dgni] == "45t_56b")
					norm = GetNormalisation(hist, -120e-6, -60e-6);
			}

			draw(scale(1e6, 1./norm), hist, "vl", StdPen(dsi), replace(datasets[dsi], "_", "\_"));
		}

		if (q_types[qi] == "y")
		{
			if (dgns[dgni] == "45b_56t")
				xlimits(0, 150, Crop);
			if (dgns[dgni] == "45t_56b")
				xlimits(-150, 0, Crop);
		}
	}
}

AttachLegend(NW, NE);
