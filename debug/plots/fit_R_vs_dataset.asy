import root;
import pad_layout;

string topDir = "../";

string f = topDir + "fit_B.root";

string d_tags[], d_labels[];
d_tags.push("45b_56t"); d_labels.push("45b\_56t");
d_tags.push("45t_56b"); d_labels.push("45t\_56b");
d_tags.push("combined"); d_labels.push("combined");

xTicksDef = LeftTicks(2., 1.);

//----------------------------------------------------------------------------------------------------

for (int di : d_tags.keys)
	NewPadLabel(d_labels[di]);

NewRow();

for (int di : d_tags.keys)
{
	NewPad("dataset/fill", "$R$");

	real R_ref = 7.096;
	draw((0, R_ref)--(7, R_ref), gray + 2pt);

	string base = "g_R_vs_dataset_group_" + d_tags[di];

	draw(RootGetObject(f, base), "p", black, mCi+2pt);

	RootObject fit = RootGetObject(f, base + "|ff_const");
	real unc = fit.rExec("GetParError", 0);

	pen p_fit = red;
	draw(shift(0, +unc), fit, p_fit + dashed);
	draw(shift(0,    0), fit, p_fit);
	draw(shift(0, -unc), fit, p_fit + dashed);

	limits((-1, 5), (8, 10), Crop);

	//AttachLegend(BuildLegend("$|t|$ from " + replace(ranges[ri], "_", " to "), S), N);
}

GShipout(vSkip = 1mm);
