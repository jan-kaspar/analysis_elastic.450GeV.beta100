import root;
import pad_layout;
include "../common.asy";

string datasets[];
datasets.push("fill7280/Totem1");
datasets.push("fill7281/Totem1");
//datasets.push("fill7282/Totem1");
//datasets.push("fill7283/Totem1");
//datasets.push("fill7284/Totem1");
//datasets.push("fill7285/Totem1");
//datasets.push("fill7286/Totem1");
//datasets.push("fill7287/Totem1");
//datasets.push("fill7288/Totem1");
//datasets.push("fill7289/Totem1");
//datasets.push("fill7290/Totem1");
//datasets.push("fill7291/Totem1");

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
	
	real n_si = 4;
	yaxis(XEquals(-n_si * sigma, false), dashed);
	yaxis(XEquals(+n_si * sigma, false), dashed);

	xlimits(-xlimit, +xlimit, Crop);
	AttachLegend(NW, NE);
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	NewRow();

	dataset = datasets[dsi];

	NewPad(false);
	label(replace("{\SetFontSizesXX\vbox{\hbox{"+dataset+"}}}", "_", "\_"));

	//MakeComparison("cuts:2,7,5,6", "discriminator 1: $\De\th_x^*$", 1e6, "\mu rad", "cut 1/h_cq1", 80, 3.0, 20, 10);
	
	MakeComparison("cuts:1,5,6,7,8,9,10", "discriminator 2: $\De\th_y^*$", 1e6, "\mu rad", "cut 2/h_cq2", xlimit=100, sigma=9, xStep=20, xstep=10);
	
	MakeComparison("cuts:1,2,5,6,8,9,10", "discriminator 7: $\De x^*$", 1., "\mu m", "cut 7/h_cq7", xlimit=5., sigma=0.5, xStep=1., xstep=0.2);
}
