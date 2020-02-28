import root;
import pad_layout;
include "../run_info.asy";

string topDir = "../../";


string datasets[];
string periods[];
datasets.push("DS-fill7281/Totem1"); periods.push("0");
//datasets.push("DS-fill7291/Totem1"); periods.push("0");

string units[], unit_labels[];
units.push("L_2_F"); unit_labels.push("L-220-fr");
units.push("L_1_F"); unit_labels.push("L-210-fr");
units.push("R_1_F"); unit_labels.push("R-210-rf");
units.push("R_2_F"); unit_labels.push("R-220-fr" );

xSizeDef = 10cm;
drawGridDef = true;

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	string dataset = datasets[dsi];
	string period = "period " + periods[dsi];

	write(dataset);

	//--------------------
	NewRow();
	
	for (int ui : units.keys)
	{
		NewPad("$y\ung{mm}$", "$\hbox{mean } x\ung{mm}$");
	
		//draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile/p"), "d0,eb", heavygreen);
		//draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile/p|ff"), "l", magenta+1pt);

		draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile max/g_x_max_vs_y"), "p", blue);
		draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile max/g_x_max_vs_y|ff"), "l", red+1pt);
		
		limits((-30, -1.5), (+30, +1.5), Crop);
		AttachLegend(unit_labels[ui], NE, NE);
	}
	
	//--------------------
	NewRow();
	
	for (int ui : units.keys)
	{
		NewPad("$y\ung{mm}$", "");
		scale(Linear, Log);
	
		draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/vertical/y_hist|y_hist"), "d0,vl", blue);
		draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/vertical/y_hist|y_hist_range"), "d0,vl", red+1pt);
	
		limits((-30, 1e2), (+30, 1e3), Crop);
		AttachLegend(unit_labels[ui], NE, NE);
	}
	
	//--------------------
	NewRow();
	
	for (int ui : units.keys)
	{
		NewPad("bottom-RP $y$ shift$\ung{mm}$", "");
		currentpad.xTicks = LeftTicks(0.5, 0.1);
	
		draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/vertical/g_max_diff"), "l,p", heavygreen, mCi+1pt+heavygreen);
	
		limits((-1.0, 0), (+1.0, 0.1), Crop);
		AttachLegend(unit_labels[ui], NE, NE);
	}

	//--------------------
	
	GShipout("alignment_details");
	//GShipout("alignment_details_" + dataset);
}
