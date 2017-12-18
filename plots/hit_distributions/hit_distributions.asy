import root;
import pad_layout;

string topDir = "../../";

TH2_palette = Gradient(blue, heavygreen, yellow, red);

string datasets[] = {
	//"DS-scheme3",
	"DS-scheme4",
	//"DS-scheme5",
	"DS-scheme6",
	//"DS-scheme7",
};

string units[] = { "L_2_F", "R_2_F" };
string unit_labels[] = { "45-220-fr", "56-220-fr" };

real sh_top[] = { 6.6, 6.0, 5.7,     7.2, 7.5, 8.2 };
real sh_bot[] = { -6.8, -6.4, -6.2, -6.3, -6.4, -7.1 };

drawGridDef = true;

/*
TH2_x_min = -10;
TH2_x_max = +10;
TH2_y_min = 40;
TH2_y_max = 65;
*/

//----------------------------------------------------------------------------------------------------

real edge = 3.6101;
real cutEdge = 2.22721 / sqrt(2);
int strips = 11;
real margin_v_e = 0.2;
real margin_v_b = 0.4;
real margin_u = 0.1;

path det_shape = (cutEdge, 0)--(edge, 0)--(edge, edge)--(0, edge)--(0, cutEdge)--cycle;
det_shape = scale(10) * rotate(45) * shift(-cutEdge/2, -cutEdge/2) * det_shape;

path hor_det_shape = shift(0, -cutEdge/sqrt(2)*10) * det_shape;

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	NewRow();

	NewPad(false);
	label("{\SetFontSizesXX " + datasets[dsi] + "}");

	string file_45b = topDir + datasets[dsi] + "/distributions_45b_56t.root";
	string file_45t = topDir + datasets[dsi] + "/distributions_45t_56b.root";

	for (int ui : units.keys)
	{
		NewPad("$x\ung{mm}$", "$y\ung{mm}$", 6cm, 6cm);
		scale(Linear, Linear, Log);

		TH2_z_max = log10(7e1);


		RootGetObject(file_45b, "hit distributions/vertical, aligned, before selection/h_y_"+units[ui]+"_vs_x_"+units[ui]+"_al_nosel");
		robj.vExec("Rebin2D", 4, 4);
		draw(robj, "p,bar");

		RootGetObject(file_45t, "hit distributions/vertical, aligned, before selection/h_y_"+units[ui]+"_vs_x_"+units[ui]+"_al_nosel");
		robj.vExec("Rebin2D", 4, 4);
		draw(robj, "p");
		
		//draw(RootGetObject(file_45t, "hit distributions/vertical, not aligned, after selection/h_y_"+units[ui]+"_vs_x_"+units[ui]+"_noal_sel"), "p");
		
		/*
		draw(shift(0, sh_top[ui])*det_shape);
		draw(shift(0, sh_bot[ui])*scale(1, -1)*det_shape);
		*/

		//draw(shift(6.2, 0)*rotate(-90)*det_shape);

		//limits((-3, -3), (+3, +7), Crop);
		//limits((-30, -9), (+30, +9), Crop);

		AttachLegend(replace(unit_labels[ui], "_", "\_"));
	}
}

GShipout(hSkip=1mm, vSkip=1mm);
