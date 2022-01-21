import root;
import pad_layout;

string topDir = "../";

string f = topDir + "fit_B.root";

string scenarios[], s_labels[];
scenarios.push("all-good_no_bckg_sub"); s_labels.push("no bckg sub");
scenarios.push("all-good_default"); s_labels.push("default");
scenarios.push("merged"); s_labels.push("merged");

string d_tags[], d_labels[];
d_tags.push("45b_56t"); d_labels.push("45b\_56t");
d_tags.push("45t_56b"); d_labels.push("45t\_56b");

xTicksDef = LeftTicks(2., 1.);

real x_min = -1, x_max = scenarios.length;

//----------------------------------------------------------------------------------------------------

string ScenarioTickLabels(real x)
{
	if (x >=0 && x < scenarios.length)
	{
		return s_labels[(int) x];
	} else {
		return "";
	}
}

xTicksDef = LeftTicks(rotate(90)*Label(""), ScenarioTickLabels, Step=1, step=0);

//----------------------------------------------------------------------------------------------------

for (int di : d_tags.keys)
	NewPadLabel(d_labels[di]);

NewRow();

for (int di : d_tags.keys)
{
	NewPad("", "$R$");

	real R_ref = 7.096;
	draw((x_min, R_ref)--(x_max, R_ref), gray + 2pt);

	for (int si : scenarios.keys)
	{
		RootObject g_R = RootGetObject(f, scenarios[si] + "_" + d_tags[di] + "/g_R_data");

		real x = si;

		real ax[] = {0.};
		real ay[] = {0.};
		g_R.vExec("GetPoint", 0, ax, ay);
		real R = ax[0], R_unc = ay[0];

		draw((x, R - R_unc)--(x, R + R_unc), red);
		draw((x, R), mCi + 2pt + red);
	}

	limits((x_min, 7), (x_max, 8.5), Crop);
}

GShipout(vSkip = 1mm);
