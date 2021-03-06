import root;
import pad_layout;
include "../common.asy";
include "../run_info.asy";

string fills[], f_datasets[];
fills.push("7280"); f_datasets.push("data/fill7280/Totem1");
fills.push("7281"); f_datasets.push("data/fill7281/Totem1");
fills.push("7282"); f_datasets.push("data/fill7282/Totem1");
fills.push("7283"); f_datasets.push("data/fill7283/Totem1");
fills.push("7284"); f_datasets.push("data/fill7284/Totem1");
fills.push("7285"); f_datasets.push("data/fill7285/Totem1");
fills.push("7289"); f_datasets.push("data/fill7289/Totem1");
fills.push("7291"); f_datasets.push("data/fill7291/Totem1");

string diagonals[], d_labels[];
pen d_pens[];
diagonals.push("45b_56t"); d_labels.push("45b -- 56t"); d_pens.push(red);
diagonals.push("45t_56b"); d_labels.push("45t -- 56b"); d_pens.push(blue);

string quantities[], q_timber[], q_labels[];
real q_maxs[];
quantities.push("vtx_x"); q_labels.push("x^*"); q_maxs.push(1000.);
quantities.push("vtx_y"); q_labels.push("y^*"); q_maxs.push(5000.);

xSizeDef = 40cm;
ySizeDef = 6cm;

//xTicksDef = LeftTicks(1., 0.5);

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

for (int qi : quantities.keys)
{
	NewPad("time$\ung{h}$", "$\si[\De^{R-L}" + q_labels[qi] + "]\ung{\mu m}$");

	for (int fi : fills.keys)
	{
		string ft = topDir + f_datasets[fi] + "/process_timber.root";

		DrawBands(fills[fi], bands="run", labels="ds", 0., q_maxs[qi]);

		for (int dgni : diagonals.keys)
		{
			string f = topDir + f_datasets[fi] + "/distributions_" + diagonals[dgni] + ".root";
			TGraph_reducePoints = 1;
			draw(scale(1./3600, 1e3), RootGetObject(f, "time dependences/gRMS_diffRL_" + quantities[qi] + "_vs_time"), "l,p", d_pens[dgni], d_labels[dgni]);
		}

		//ylimits(0., q_maxs[qi], Crop);
	}

	GShipout(quantities[qi] + "_diffRL_vs_time");
}
