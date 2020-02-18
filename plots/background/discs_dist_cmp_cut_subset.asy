import root;
import pad_layout;

string datasets[];
datasets.push("DS-fill7280/Totem1");
datasets.push("DS-fill7281/Totem1");
//datasets.push("DS-fill7282/Totem1");
//datasets.push("DS-fill7283/Totem1");
//datasets.push("DS-fill7284/Totem1");
//datasets.push("DS-fill7285/Totem1");
datasets.push("DS-fill7286/Totem1");
//datasets.push("DS-fill7287/Totem1");
//datasets.push("DS-fill7288/Totem1");
//datasets.push("DS-fill7289/Totem1");
//datasets.push("DS-fill7290/Totem1");
//datasets.push("DS-fill7291/Totem1");

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };

string topDir = "../../";

xSizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

string dataset;
string diagonal;

void MakeComparison(string quantity, real xscale, string unit, string obj, real xlimit, real sigma,
	real xStep, real xstep,
	string combinations[], pen comb_pens[])
{
	NewPad(quantity+"$\ung{"+unit+"}$", "", xTicks=LeftTicks(xStep, xstep));
	scale(Linear, Log(true));
	for (int ci : combinations.keys)
	{
		string f = topDir+"/background_studies/"+dataset+"/"+combinations[ci]+"/distributions_"+diagonal+".root";
		draw(scale(xscale, 1), RootGetObject(f, "elastic cuts/"+obj), "vl",
			comb_pens[ci], replace(combinations[ci], "_", "\_"));	
	}

	yaxis(XEquals(-4*sigma, false), dashed);
	yaxis(XEquals(+4*sigma, false), dashed);

	xlimits(-xlimit, +xlimit, Crop);
	AttachLegend(quantity, NW, NE);
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	dataset = datasets[dsi];

	write("* " + dataset);

	for (int dgi : diagonals.keys)
	{
		NewRow();

		diagonal = diagonals[dgi];

		NewPad(false);
		label(replace("{\SetFontSizesXX\vbox{\hbox{"+dataset+"}\hbox{"+dgn_labels[dgi]+"}}}", "_", "\_"));

		string combinations[];
		pen comb_pens[];
		
		combinations.push("no_cuts"); comb_pens.push(black+2pt);
		combinations.push("cuts:1"); comb_pens.push(orange);
		combinations.push("cuts:1,2"); comb_pens.push(cyan);
		combinations.push("cuts:1,2,5"); comb_pens.push(magenta);
		combinations.push("cuts:1,2,5,6"); comb_pens.push(gray);
		combinations.push("cuts:1,2,5,6,8"); comb_pens.push(blue);
		combinations.push("cuts:1,2,5,6,8,9"); comb_pens.push(heavygreen);
		combinations.push("cuts:1,2,5,6,8,9,10"); comb_pens.push(red+2pt);
		
		MakeComparison("$\De^{\rm R-L} x^*$", 1e0, "mm", "cut 7/h_cq7", xlimit=5, sigma=0.5, xStep=1., xstep=0.2, combinations, comb_pens);
		
		//--------------------
		
		string combinations[];
		pen comb_pens[];
		
		combinations.push("no_cuts"); comb_pens.push(black+2pt);
		combinations.push("cuts:1"); comb_pens.push(orange);
		combinations.push("cuts:1,5"); comb_pens.push(cyan);
		combinations.push("cuts:1,5,6"); comb_pens.push(magenta);
		combinations.push("cuts:1,5,6,7"); comb_pens.push(gray);
		combinations.push("cuts:1,5,6,7,8"); comb_pens.push(blue);
		combinations.push("cuts:1,5,6,7,8,9"); comb_pens.push(heavygreen);
		combinations.push("cuts:1,5,6,7,8,9,10"); comb_pens.push(red+2pt);
		
		MakeComparison("$\De\th_y^*$", 1e6, "\mu rad", "cut 2/h_cq2", xlimit=100, sigma=9, xStep=20, xstep=10, combinations, comb_pens);
	}

	GShipout("discs_dist_cmp_cut_subset_" + replace(dataset, "/", "_") + ".pdf");
}