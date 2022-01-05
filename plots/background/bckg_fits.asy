import root;
import pad_layout;
include "../common.asy";

string datasets[], d_labels[];
datasets.push("fill7280/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7281/Totem1"); d_labels.push("crystal coll.");
datasets.push("fill7282/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7283/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7284/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7285/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7289/Totem1"); d_labels.push("crystal coll.");
datasets.push("fill7291/Totem1"); d_labels.push("crystal coll.");
datasets.push("all-good/Totem1/default"); d_labels.push("mix");

xSizeDef = 10cm;

string binning = "sb1";

TGraph_errorBar = None;

real x_max = 0.01;
TGraph_x_min = 3.1e-4;
TGraph_x_max = x_max;

real y_min = -0.005, y_max = +0.035;

//----------------------------------------------------------------------------------------------------

NewPad(false);
NewPadLabel("45 bot -- 56 bot");
NewPadLabel("45 top -- 56 top");
NewPadLabel("mean");

for (int dsi : datasets.keys)
{
	NewRow();

	NewPadLabel("\vbox{\hbox{" + datasets[dsi] + "}\hbox{(" + d_labels[dsi] + ")}}");

	string f = topDir + "data/" + datasets[dsi] + "/background_fit_combined.root";
	
	string base = binning + "/after_acc_corr/bb/g";
	NewPad("$|t|\ung{GeV^2}$", "relative background contamination");
	draw(RootGetObject(f, base), "p", blue, mCi+blue);
	draw(RootGetObject(f, base + "|ff"), "l", red+1pt);
	limits((0, y_min), (x_max, y_max), Crop);

	string base = binning + "/after_acc_corr/tt/g";
	NewPad("$|t|\ung{GeV^2}$", "relative background contamination");
	draw(RootGetObject(f, base), "p", blue, mCi+blue);
	draw(RootGetObject(f, base + "|ff"), "l", red+1pt);
	limits((0, y_min), (x_max, y_max), Crop);

	string base = binning + "/after_acc_corr/mean/g";
	NewPad("$|t|\ung{GeV^2}$", "relative background contamination");
	draw(RootGetObject(f, base), "p", blue, mCi+blue);
	draw(RootGetObject(f, base + "|ff"), "l", red+1pt);
	limits((0, y_min), (x_max, y_max), Crop);
}

GShipout(vSkip=0mm);
