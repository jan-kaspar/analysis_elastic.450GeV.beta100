import root;
import pad_layout;

string topDir = "../../";

string datasets[];
datasets.push("data/fill7281/Totem1");
datasets.push("data/fill7291/Totem1");

string units[] = { "L_2_F", "L_1_F", "R_1_F", "R_2_F" };
string unit_labels[] = { "45-220-fr", "45-210-fr", "56-210-fr", "56-220-fr" };
//string unit_labels[] = { "XRPV.B6L5.B2", "XRPV.D6L5.B2", "XRPV.D6R5.B1", "XRPV.B6R5.B1" };

drawGridDef = true;

TH2_palette = Gradient(white, blue, heavygreen, yellow, red, black);

/*
TH2_x_min = -10;
TH2_x_max = +10;
*/
TH2_y_min = -30;
TH2_y_max = +30;

xTicksDef = LeftTicks(5., 1.);

string selection = "before selection";
//string selection = "after selection";

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

		TH2_z_min = 1e0;
		TH2_z_max = 5e3;

		string tag;
		if (selection == "before selection") tag = "_al_nosel";
		if (selection == "after selection") tag = "_al_sel";

		RootGetObject(file_45b, "hit distributions/vertical, aligned, "+selection+"/h2_y_"+units[ui]+"_vs_x_"+units[ui]+tag);
		robj.vExec("Rebin2D", 2, 4);
		draw(robj, "p,bar");

		RootGetObject(file_45t, "hit distributions/vertical, aligned, "+selection+"/h2_y_"+units[ui]+"_vs_x_"+units[ui]+tag);
		robj.vExec("Rebin2D", 2, 4);
		draw(robj, "p");
		
		//draw(RootGetObject(file_45t, "hit distributions/vertical, not aligned, after selection/h2_y_"+units[ui]+"_vs_x_"+units[ui]+"_noal_sel"), "p");

		limits((-15, -30), (15, 30), Crop);

		AttachLegend(replace(unit_labels[ui], "_", "\_"));
	}
}

GShipout(hSkip=1mm, vSkip=1mm);
