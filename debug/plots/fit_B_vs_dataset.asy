import root;
import pad_layout;

string topDir = "../";

string f = topDir + "fit_B.root";

string ranges[];
pen r_pens[];
ranges.push("0.005_0.010"); r_pens.push(blue);
ranges.push("0.010_0.015"); r_pens.push(red);
ranges.push("0.015_0.020"); r_pens.push(heavygreen);
ranges.push("0.020_0.025"); r_pens.push(magenta);

string d_tags[], d_labels[];
d_tags.push("45b_56t"); d_labels.push("45b\_56t");
d_tags.push("45t_56b"); d_labels.push("45t\_56b");
d_tags.push("combined"); d_labels.push("combined");

xTicksDef = LeftTicks(2., 1.);

//----------------------------------------------------------------------------------------------------

for (int di : d_tags.keys)
{
	NewRow();

	NewPadLabel(d_labels[di]);

	for (int ri : ranges.keys)
	{
		NewPad("dataset/fill", "$\d\si/\d t\ung{mb/GeV^2}$");

		real B_ref = 17;
		draw((0, B_ref)--(7, B_ref), gray + 2pt);

		string base = "g_B_vs_dataset_group_" + d_tags[di] + "_range_" + ranges[ri];

		draw(RootGetObject(f, base), "p", r_pens[ri], mCi+2pt+r_pens[ri]);

		RootObject fit = RootGetObject(f, base + "|ff_const");
		real unc = fit.rExec("GetParError", 0);

		draw(shift(0, +unc), fit, r_pens[ri] + dashed);
		draw(shift(0,    0), fit, r_pens[ri]);
		draw(shift(0, -unc), fit, r_pens[ri] + dashed);

		limits((-1, 0), (8, 70), Crop);

		AttachLegend(BuildLegend("$|t|$ from " + replace(ranges[ri], "_", " to "), S), N);
	}
}
