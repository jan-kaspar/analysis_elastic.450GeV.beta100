import root;
import pad_layout;

string topDir = "../../../acceptance_tests/";

string diagonals[] = {
	"45b_56t",
	"45t_56b",
};

string th_x_strs[] = {
	"+0.0E+00",
	"+1.0E-04",
	"+2.0E-04",
	"+3.0E-04",
};

string f = topDir + "validation_gaussian_approx.root";

//----------------------------------------------------------------------------------------------------

for (string diagonal : diagonals)
{
	NewRow();

	NewPad(false);
	label(replace(diagonal, "_", " -- "));

	//----------------------------

	for (string th_x_str : th_x_strs)
	{
		NewPad("$\th_y^*\ung{\mu rad}$", "$A_{\rm sm}(\th_x^*, \th_y^*)$");
		currentpad.xTicks = LeftTicks(20., 10.);
	
		draw(scale(1e6, 1.), RootGetObject(f, diagonal+"/g_with_app_A_th_x_" + th_x_str), blue);
		draw(scale(1e6, 1.), RootGetObject(f, diagonal+"/g_without_app_A_th_x_" + th_x_str), red+dashed+1pt);
	
		if (diagonal == "45b_56t")
			limits((20, 0), (80, 1), Crop);
		else
			limits((-80, 0), (-20, 1), Crop);
	
		AttachLegend("$\th_x^* = $" + th_x_str, NW, NW);
	}
	
	//----------------------------
	
	NewPad("$|t|\ung{GeV^2}$", "$A_\ph(t)$");
	draw(RootGetObject(f, diagonal+"/g_A_t_with_app"), blue, "with approximation");
	draw(RootGetObject(f, diagonal+"/g_A_t_without_app"), red+dashed+1pt, "without approximation");
	
	limits((0, 0), (0.005, 0.5), Crop);

	//----------------------------
	
	frame f_legend = BuildLegend();
	
	NewPad(false);
	add(f_legend);
}
