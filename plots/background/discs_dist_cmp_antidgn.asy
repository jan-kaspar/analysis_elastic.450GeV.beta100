import root;
import pad_layout;
include "../common.asy";

string datasets[], d_labels[];
datasets.push("fill7280/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7281/Totem1"); d_labels.push("crystal coll.");
datasets.push("fill7282/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7283/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7284/Totem1"); d_labels.push("standard coll.");
datasets.push("fill7285/Totem1"); d_labels.push("standard coll.");
//datasets.push("fill7286/Totem1"); d_labels.push("BAD");
//datasets.push("fill7287/Totem1"); d_labels.push("BAD");
//datasets.push("fill7288/Totem1"); d_labels.push("BAD");
datasets.push("fill7289/Totem1"); d_labels.push("crystal coll.");
//datasets.push("fill7290/Totem1"); d_labels.push("BAD");
datasets.push("fill7291/Totem1"); d_labels.push("crystal coll.");

string diagonals[] = { "45b_56t", "45t_56b", "anti_45b_56b", "anti_45t_56t" };
string dgn_labels[] = { "45 bot -- 56 top", "45 top -- 56 bot", "45 bot -- 56 bot", "45 top -- 56 top" };

xSizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

string dataset;

void MakeComparison(string cut_str, string quantity, real xscale, string unit, string obj, real xlimit, real sigma,
	real xStep, real xstep)
{
	NewPad(quantity+"$\ung{"+unit+"}$", "", xTicks=LeftTicks(xStep, xstep));
	scale(Linear, Log(true));

	AddToLegend("<" + quantity);
	AddToLegend("<(" + cut_str + ")");
	
	string dir = topDir+"studies/background/"+dataset+"/"+cut_str;

	for (int dgni : diagonals.keys)
		draw(scale(xscale, 1), RootGetObject(dir + "/distributions_"+diagonals[dgni]+".root", "elastic cuts/"+obj),
			"vl", StdPen(dgni+1), dgn_labels[dgni]);
	
	xlimits(-xlimit, +xlimit, Crop);

	real n_si = 4;
	yaxis(XEquals(-n_si * sigma, false), dashed);
	yaxis(XEquals(+n_si * sigma, false), dashed);

	AttachLegend(NW, NE);
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	NewRow();

	dataset = datasets[dsi];

	NewPad(false);
	label(replace("{\SetFontSizesXX\vbox{\hbox{"+dataset+"}\hbox{(" + d_labels[dsi] + ")}}}", "_", "\_"));

	MakeComparison("cuts:2,5,6,7,8,9,10", "discriminator 1: $\De^{R-L}\th_x^*$", 1e6, "\mu rad", "cut 1/h_cq1", xlimit=300, xStep=100, xstep=50, sigma=29);
	
	MakeComparison("cuts:1,5,6,7,8,9,10", "discriminator 2: $\De^{R-L}\th_y^*$", 1e6, "\mu rad", "cut 2/h_cq2", xlimit=100, sigma=8, xStep=20, xstep=10);
	
	MakeComparison("cuts:1,2,6,7,8,9,10", "discriminator 5: $\De^{F-N} y^R$", 1, "mm", "cut 5/h_cq5", xlimit=1, xStep=0.2, xstep=0.1, sigma=0.08);
	
	MakeComparison("cuts:1,2,5,7,8,9,10", "discriminator 6: $\De^{F-N} y^L$", 1, "mm", "cut 6/h_cq6", xlimit=1, xStep=0.2, xstep=0.1, sigma=0.08);
	
	MakeComparison("cuts:1,2,5,6,8,9,10", "discriminator 7: $\De^{R-L} x^*$", 1., "mm", "cut 7/h_cq7", xlimit=5., sigma=0.5, xStep=1., xstep=0.2);

	MakeComparison("cuts:1,2,5,6,7,9,10", "discriminator 8: $\De^{R-L} y^*$", 1., "mm", "cut 8/h_cq8", xlimit=20, xStep=5, xstep=1, sigma=2.8);
	
	MakeComparison("cuts:1,2,5,6,7,8,10", "discriminator 9: $\De^{F-N} x^R$", 1, "mm", "cut 9/h_cq9", xlimit=1.5, xStep=0.5, xstep=0.1, sigma=0.14);
	
	MakeComparison("cuts:1,2,5,6,7,8,9", "discriminator 10: $\De^{F-N} x^L$", 1, "mm", "cut 10/h_cq10", xlimit=1.5, xStep=0.5, xstep=0.1, sigma=0.14);
}
