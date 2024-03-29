import root;
import pad_layout;
include "../common.asy";
include common_code;

//----------------------------------------------------------------------------------------------------

string datasets[] = { "merged" };

//string diagonals[] = { "45b_56t", "45t_56b", "combined" };
//string diagonals_long[] = { "45 bottom - 56 top", "45 top - 56 bottom", "combined" };

string diagonals[] = { "combined" };
string diagonals_long[] = { "combined" };

xSizeDef = 8cm;
ySizeDef = 6cm;

A_ref = 230.;
B_ref = 20.0;
ref_str = MakeRefStr("");

//TH1_x_min = 0.04;

//----------------------------------------------------------------------------------------------------

frame fLegend;

void DrawSet(string binning)
{
	for (int di : diagonals.keys)
	{
		NewPad("$|t|\ung{GeV^2}$", "${\d\si/\d t - \hbox{ref} \over \hbox{ref}}\ ,\ \ \hbox{ref} = $ "+ref_str+"");
		currentpad.xTicks = LeftTicks(0.005, 0.001);
	
		for (int dsi : datasets.keys)
		{
			string dataset = datasets[dsi];
	
			pen p = StdPen(dsi+1);

			DrawRelDiff(
				RootGetObject(topDir+"data/merged.root", binning+"/"+datasets[dsi]+"/"+diagonals[di]+"/h_dsdt"),
				p, datasets[dsi]);
			
			limits((0, -0.05), (0.03, 0.05), Crop);
			xaxis(YEquals(0, false), dashed);
		}
	
		fLegend = BuildLegend("binning: " + binning);
		currentpicture.legend.delete();
		AttachLegend("diagonal: " + diagonals_long[di]);
		//AttachLegend("$\sqrt s = 13\un{TeV}$");
	}
		
	NewPad(false);
	add(fLegend);
}

//----------------------------------------------------------------------------------------------------

DrawSet("sb2");
