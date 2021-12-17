import root;
import pad_layout;
include "../common.asy";

string fills[], f_datasets[];
fills.push("7280"); f_datasets.push("data/fill7280/Totem1");
fills.push("7281"); f_datasets.push("data/fill7281/Totem1");
//fills.push("7282"); f_datasets.push("data/fill7282/Totem1");
//fills.push("7283"); f_datasets.push("data/fill7283/Totem1");
//fills.push("7284"); f_datasets.push("data/fill7284/Totem1");
//fills.push("7285"); f_datasets.push("data/fill7285/Totem1");
//fills.push("7289"); f_datasets.push("data/fill7289/Totem1");
fills.push("7291"); f_datasets.push("data/fill7291/Totem1");

string diagonals[], d_labels[];
pen d_pens[];
diagonals.push("45b_56t"); d_labels.push("45b -- 56t"); d_pens.push(red);
diagonals.push("45t_56b"); d_labels.push("45t -- 56b"); d_pens.push(blue);

string projections[], p_paths[], p_h_labels[], p_v_labels[];
real p_maxs[], p_v_mins[], p_v_maxs[];
projections.push("x"); p_paths.push("selected - angles/th_x_sigmaRL_vs_th_x"); p_h_labels.push("$\th^*_x\ung{\mu rad}$"); p_v_labels.push("RMS of $\De^{R-L}\th^*_x\ung{\mu rad}$"); p_maxs.push(350); p_v_mins.push(10); p_v_maxs.push(40);
projections.push("y"); p_paths.push("selected - angles/th_y_sigmaRL_vs_th_y"); p_h_labels.push("$\th^*_y\ung{\mu rad}$"); p_v_labels.push("RMS of $\De^{R-L}\th^*_y\ung{\mu rad}$"); p_maxs.push(150); p_v_mins.push(5); p_v_maxs.push(10);

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int pi : projections.keys)
	NewPadLabel(projections[pi]);

for (int dsi : f_datasets.keys)
{
	NewRow();

	NewPadLabel(f_datasets[dsi]);

	for (int pi : projections.keys)
	{
		NewPad(p_h_labels[pi], p_v_labels[pi]);

		for (int dgni : diagonals.keys)
		{
			string f = topDir + f_datasets[dsi] + "/distributions_" + diagonals[dgni] + ".root";
			draw(scale(1e6, 1e6), RootGetObject(f, p_paths[pi]), "l,p", d_pens[dgni], d_labels[dgni]);	
		}

		limits((-p_maxs[pi], p_v_mins[pi]), (+p_maxs[pi], p_v_maxs[pi]), Crop);
	}

	AttachLegend(NW, NE);
}

GShipout(vSkip=0mm);
