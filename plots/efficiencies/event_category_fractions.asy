import root;
import pad_layout;

include "../run_info.asy";

string topDir = "../../";

TH2_palette = Gradient(blue, heavygreen, yellow, red);

string fills[], f_datasets[];
/*
f_datasets.push("data/fill7280/Totem1"); fills.push("7280");
f_datasets.push("data/fill7281/Totem1"); fills.push("7281");
f_datasets.push("data/fill7282/Totem1"); fills.push("7282");
f_datasets.push("data/fill7283/Totem1"); fills.push("7283");
f_datasets.push("data/fill7284/Totem1"); fills.push("7284");
f_datasets.push("data/fill7285/Totem1"); fills.push("7285");
f_datasets.push("data/fill7286/Totem1"); fills.push("7286");
f_datasets.push("data/fill7287/Totem1"); fills.push("7287");
f_datasets.push("data/fill7288/Totem1"); fills.push("7288");
f_datasets.push("data/fill7289/Totem1"); fills.push("7289");
*/
f_datasets.push("data/fill7290/Totem1"); fills.push("7290");
//f_datasets.push("data/fill7290/ZeroBias"); fills.push("7290");
f_datasets.push("data/fill7291/Totem1"); fills.push("7291");
//f_datasets.push("data/fill7291/ZeroBias"); fills.push("7291");

string diagonals[], dgn_labels[];
diagonals.push("45b_56t"); dgn_labels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); dgn_labels.push("45 top -- 56 bot");

string rps[], rp_labels[];
rps.push("L_2_F"); rp_labels.push("45-220-fr");
rps.push("L_1_F"); rp_labels.push("45-210-fr");
rps.push("R_1_F"); rp_labels.push("56-210-fr");
rps.push("R_2_F"); rp_labels.push("56-220-fr");

TGraph_errorBar = None;

//xTicksDef = LeftTicks(1., 0.5);
//yTicksDef = RightTicks(0.01, 0.005);

//----------------------------------------------------------------------------------------------------

NewPad(false);
NewPad(false);
for (int rpi : rps.keys)
{
	NewPadLabel(rp_labels[rpi]);
}

for (int dsi : f_datasets.keys)
{
	NewRow();

	NewPadLabel(f_datasets[dsi] + ":");

	string f = topDir + f_datasets[dsi] + "/pileup_combined.root";

	for (int dgni : diagonals.keys)
	{
		NewRow();

		NewPad(false);
		NewPadLabel(dgn_labels[dgni]);
		
		for (int rpi : rps.keys)
		{
			NewPad("time $\ung{h}$", "event fraction");

			DrawBands(fills[dsi], bands="run", labels="ds", 0., 1.);

			draw(scale(1./3600, 1.), RootGetObject(f, diagonals[dgni] + "/" + rps[rpi] + "/pl_suff/rel"), "p", cyan+1pt, mCi+2pt+cyan, "pl\_suff");
			draw(scale(1./3600, 1.), RootGetObject(f, diagonals[dgni] + "/" + rps[rpi] + "/pat_suff/rel"), "p", blue+1pt, mCi+2pt+blue, "pat\_suff");
                                  
			draw(scale(1./3600, 1.), RootGetObject(f, diagonals[dgni] + "/" + rps[rpi] + "/tr/rel"), "p", heavygreen+1pt, mCi+2pt+heavygreen, "tr");
			
			draw(scale(1./3600, 1.), RootGetObject(f, diagonals[dgni] + "/" + rps[rpi] + "/pat_more/rel"), "p", red+1pt, mCi+2pt+red, "pat\_more");

			ylimits(0, 1., Crop);
		}
	}

	frame f_legend = BuildLegend();

	NewPad(false);
	attach(f_legend);
}

GShipout("event_category_fractions", vSkip=1mm);
