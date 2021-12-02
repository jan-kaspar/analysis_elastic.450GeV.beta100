import root;
import pad_layout;

string topDir = "../";

string f = topDir + "x_reco.root";

string coefficients[];
real c_defaults[], c_scales[];
coefficients.push("A"); c_defaults.push(1); c_scales.push(1);
coefficients.push("B"); c_defaults.push(0); c_scales.push(0.0001);
coefficients.push("C"); c_defaults.push(0); c_scales.push(1e4);
coefficients.push("D"); c_defaults.push(1); c_scales.push(1);

string al_values[];
al_values.push("-0.010");
al_values.push("-0.005");
al_values.push("+0.000");
al_values.push("+0.005");
al_values.push("+0.010");

//yTicksDef = RightTicks(0.5, 0.1);

//----------------------------------------------------------------------------------------------------

for (int ci : coefficients.keys)
{
	NewPad("$\be$", coefficients[ci]);

	real y_def = c_defaults[ci];
	real y_sc = c_scales[ci];

	for (int ali : al_values.keys)
	{
		pen p = StdPen(ali);

		draw(RootGetObject(f, "al=" + al_values[ali] + "/g_" + coefficients[ci]), "l", p, "al = " + al_values[ali]);
	}

	limits((-0.10, y_def - y_sc), (+0.05, y_def + y_sc), Crop);

	yaxis(XEquals(0, false), dashed);

	xaxis(YEquals(y_def, false), dashed);

	if (coefficients[ci] == "B")
	{
		real slope = 50e-6;
		xaxis(YEquals(+slope, false), magenta);
		xaxis(YEquals(-slope, false), magenta);
	}
}

frame f_legend = BuildLegend();
NewPad(false);
attach(f_legend);
