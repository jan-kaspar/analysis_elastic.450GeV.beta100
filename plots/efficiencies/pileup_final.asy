import root;
import pad_layout;

include "../run_info.asy";

string topDir = "../../";

string fills[], f_datasets[];
f_datasets.push("data/fill7280/ZeroBias"); fills.push("7280");
f_datasets.push("data/fill7281/ZeroBias"); fills.push("7281");
f_datasets.push("data/fill7282/ZeroBias"); fills.push("7282");
f_datasets.push("data/fill7283/ZeroBias"); fills.push("7283");
f_datasets.push("data/fill7284/ZeroBias"); fills.push("7284");
f_datasets.push("data/fill7285/ZeroBias"); fills.push("7285");
f_datasets.push("data/fill7286/ZeroBias"); fills.push("7286");
f_datasets.push("data/fill7287/ZeroBias"); fills.push("7287");
f_datasets.push("data/fill7288/ZeroBias"); fills.push("7288");
f_datasets.push("data/fill7289/ZeroBias"); fills.push("7289");
f_datasets.push("data/fill7290/ZeroBias"); fills.push("7290");
f_datasets.push("data/fill7291/ZeroBias"); fills.push("7291");

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45 bot -- 56 top", "45 top -- 56 bot" };

string template = "dgn/# && #, L || R";

string criteria[] = { "pat_suff_destr", "pl_suff_destr" };

xSizeDef = 10cm;

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

frame fr_leg;

NewPad(false);
for (int di : diagonals.keys)
	NewPadLabel(dgn_labels[di]);

for (int dsi : f_datasets.keys)
{
	NewRow();

	NewPadLabel(f_datasets[dsi]);

	string f = topDir + f_datasets[dsi]+"/pileup_combined.root";

	for (int di : diagonals.keys)
	{
		string dgn = diagonals[di];

		real y_max = 0.3;
		
		NewPad("time$\ung{h}$", "destructive pile-up probability");
		DrawBands(fills[dsi], bands="run", labels="ds", 0, y_max);
		
		for (int ci : criteria.keys)
		{
			string element = replace(template, "#", criteria[ci]);
			pen p = StdPen(ci);

			RootObject obj = RootGetObject(f, dgn+"/"+element+"/rel", search=false, error=false);
			if (obj.valid)
				draw(swToHours, obj, "p", p, mCi+2pt+p, replace(criteria[ci], "_", "\_"));
		}
		
		ylimits(0, y_max, Crop);
		//limits((2, 0), (3.6, y_max), Crop);
		
		fr_leg = BuildLegend();
	}
}

NewPad(false);
attach(fr_leg);

GShipout("pileup_final", hSkip=1mm, vSkip=0mm);
