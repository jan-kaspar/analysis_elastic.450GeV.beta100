import root;
import pad_layout;

include "../run_info.asy";

string topDir = "../../";

string datasets[], ds_labels[];
datasets.push("DS1_ZeroBias/block0"); ds_labels.push("DS1");
//datasets.push("DS3_ZeroBias/block0"); ds_labels.push("DS3");

string diagonals[] = { "45b", "45t" };
string dgn_labels[] = { "45 bot -- 56 top", "45 top -- 56 bot" };

string template = "dgn/# && #, L || R";

string criteria[] = { "pat_suff_destr", "pl_suff_destr" };

xSizeDef = 10cm;

//----------------------------------------------------------------------------------------------------

TGraph_errorBar = None;

int c = 0;
frame fr_leg;

for (int dsi : datasets.keys)
{
	string f = topDir + datasets[dsi]+"/pileup_combined.root";

	for (int di : diagonals.keys)
	{
		string dgn = diagonals[di];

		++c;
		
		NewPad(false, c, 0);
		label("\vbox{\SetFontSizesXX\hbox{"+ds_labels[dsi]+"}\hbox{"+dgn_labels[di]+"}}");
	
	
		real y_max = 1.0;
		
		NewPad("time$\ung{h}$", "destructive pile-up probability", c, 1);
		DrawRunBands(ds_labels[dsi], 0, y_max);
		
		for (int ci : criteria.keys)
		{
			string element = replace(template, "#", criteria[ci]);
			pen p = StdPen(ci);
			draw(swToHours, RootGetObject(f, dgn+"/"+element+"/rel", search=false), "p", p, mCi+2pt+p, replace(criteria[ci], "_", "\_"));
		}
		
		ylimits(0, y_max, Crop);
		//limits((2, 0), (3.6, y_max), Crop);
		
		fr_leg = BuildLegend();
	}
}

++c;

NewPad(false, c, 1);
attach(fr_leg);

GShipout(hSkip=1mm, vSkip=0mm);
