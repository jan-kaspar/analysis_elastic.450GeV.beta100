import root;
import pad_layout;

string topDir = "../../";

string datasets[];
datasets.push("data/fill7281/Totem1");
datasets.push("data/fill7291/Totem1");

string dgns[], d_labels[];
dgns.push("45b_56t"); d_labels.push("45 bot -- 56 top");
dgns.push("45t_56b"); d_labels.push("45 top -- 56 bot");

bool rebin = false;

real th_min = 25, th_max = 60;

real cut_L = 34, cut_R = 34, cut_G = 38;

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
		real sign = 0;

		if (dgns[dgni] == "45b_56t")
		{
			sign = +1;
			TH2_x_min = th_min * 1e-6; TH2_y_min = th_min * 1e-6;
			TH2_x_max = th_max * 1e-6; TH2_y_max = th_max * 1e-6;
		}

		if (dgns[dgni] == "45t_56b")
		{
			sign = -1;
			TH2_x_min = -th_max * 1e-6; TH2_y_min = -th_max * 1e-6;
			TH2_x_max = -th_min * 1e-6; TH2_y_max = -th_min * 1e-6;
		}

		NewPad("$\th^{*,R}_y\ung{\mu rad}$", "$\th^{*,L}_y\ung{\mu rad}$");

		RootObject h2 = RootGetObject(topDir + datasets[dsi] + "/distributions_" + dgns[dgni] + ".root", "selected - angles/h2_th_y_L_vs_th_y_R_nmid_th_x");

		if (rebin)
			h2.vExec("Rebin2D", 4, 4);

		draw(scale(sign*1e6, sign*1e6), h2);

		draw((th_min, cut_L)--(th_max, cut_L), black+1pt);
		draw((cut_R, th_min)--(cut_R, th_max), black+1pt);

		draw((th_min, 2*cut_G - th_min)--(th_max, 2*cut_G - th_max), cyan+1pt);

		draw((th_min, th_min)--(th_max, th_max), magenta);

		limits((th_min, th_min), (th_max, th_max), Crop);
	}
}

GShipout(vSkip=0mm);
