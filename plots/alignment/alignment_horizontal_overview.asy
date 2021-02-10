import root;
import pad_layout;
include "../common.asy";
include "../run_info.asy";

string datasets[];
string periods[][];
datasets.push("data/fill7280/Totem1"); periods.push(new string[] { "0", "1"} );
datasets.push("data/fill7281/Totem1"); periods.push(new string[] { "0" } );
datasets.push("data/fill7282/Totem1"); periods.push(new string[] { "0", "1"} );
datasets.push("data/fill7283/Totem1"); periods.push(new string[] { "0" } );
datasets.push("data/fill7284/Totem1"); periods.push(new string[] { "0", "1"} );
datasets.push("data/fill7285/Totem1"); periods.push(new string[] { "0" } );
datasets.push("data/fill7289/Totem1"); periods.push(new string[] { "0", "1"} );
datasets.push("data/fill7291/Totem1"); periods.push(new string[] { "0", "1"} );

string units[], unit_labels[];
real u_ycut_neg[], u_ycut_pos[];
units.push("L_2_F"); unit_labels.push("L-220-fr"); u_ycut_neg.push(-6.); u_ycut_pos.push(+6.);
units.push("L_1_F"); unit_labels.push("L-210-fr"); u_ycut_neg.push(-5.5); u_ycut_pos.push(+5.5);
units.push("R_1_F"); unit_labels.push("R-210-rf"); u_ycut_neg.push(-5.5); u_ycut_pos.push(+5.5);
units.push("R_2_F"); unit_labels.push("R-220-fr" ); u_ycut_neg.push(-6.); u_ycut_pos.push(+6.);

xSizeDef = 10cm;
drawGridDef = true;

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

NewPad(false);

for (int ui : units.keys)
	NewPadLabel(unit_labels[ui]);

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	string dataset = datasets[dsi];

	for (int pi : periods[dsi].keys)
	{
		string period = "period " + periods[dsi][pi];

		NewRow();

		NewPadLabel("\vbox{\hbox{" + dataset + "}\hbox{" + period + "}}");
		
		for (int ui : units.keys)
		{
			NewPad("$y\ung{mm}$", "$\hbox{mean } x\ung{mm}$");
		
			draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile max/g_x_max_vs_y"), "p", blue);
			draw(RootGetObject(topDir+dataset+"/alignment.root", period + "/unit "+units[ui]+"/horizontal/horizontal profile max/g_x_max_vs_y|ff"), "l", red+1pt);
			
			limits((-12, -1.5), (+12, +1.5), Crop);
			//limits((+4, -1.5), (+12, +1.5), Crop);

			yaxis(XEquals(u_ycut_neg[ui], false), heavygreen+dashed);
			yaxis(XEquals(u_ycut_pos[ui], false), heavygreen+dashed);

			AttachLegend(unit_labels[ui], NE, NE);
		}
	}
}
