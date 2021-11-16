import root;
import pad_layout;

string topDir = "../";

string f = topDir + "fit_B.root";

string datasets[] = {
	"merged_45b_56t",
	"merged_45t_56b",
};

string ranges[];
pen r_pens[];
ranges.push("0.005_0.010"); r_pens.push(blue);
ranges.push("0.010_0.015"); r_pens.push(red);
ranges.push("0.015_0.020"); r_pens.push(heavygreen);
ranges.push("0.020_0.025"); r_pens.push(magenta);

//----------------------------------------------------------------------------------------------------

real Reference(real t)
{
	return 216 * exp(-17 * t);
}

//----------------------------------------------------------------------------------------------------

for (string dataset : datasets)
{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");

	draw(graph(Reference, 0, 0.025), gray+2pt);

	draw(RootGetObject(f, dataset + "/h_dsdt"), "eb", black);
	
	for (int ri : ranges.keys)
	{
		draw(RootGetObject(f, dataset + "/fit_range_" + ranges[ri]), r_pens[ri] + 1pt);
	}

	limits((0, 100), (0.025, 300), Crop);

	AttachLegend(BuildLegend(replace(dataset, "_", "-"), S), N);
}
