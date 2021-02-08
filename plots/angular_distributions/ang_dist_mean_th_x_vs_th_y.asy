import root;
import pad_layout;

string topDir = "../../";

string datasets[], dataset_fills[];
//datasets.push("DS-fill7280/Totem1"); dataset_fills.push("7280");
datasets.push("DS-fill7281/Totem1"); dataset_fills.push("7281");
//datasets.push("DS-fill7282/Totem1"); dataset_fills.push("7282");
//datasets.push("DS-fill7283/Totem1"); dataset_fills.push("7283");
//datasets.push("DS-fill7284/Totem1"); dataset_fills.push("7284");
//datasets.push("DS-fill7285/Totem1"); dataset_fills.push("7285");
//datasets.push("DS-fill7286/Totem1"); dataset_fills.push("7286");
//datasets.push("DS-fill7287/Totem1"); dataset_fills.push("7287");
//datasets.push("DS-fill7288/Totem1"); dataset_fills.push("7288");
datasets.push("DS-fill7289/Totem1"); dataset_fills.push("7289");
//datasets.push("DS-fill7290/Totem1"); dataset_fills.push("7290");
datasets.push("DS-fill7291/Totem1"); dataset_fills.push("7291");

string diagonals[], diagonal_labels[];
pen diagonal_pens[];
diagonals.push("45b_56t"); diagonal_labels.push("45 bot -- 56 top"); diagonal_pens.push(blue);
diagonals.push("45t_56b"); diagonal_labels.push("45 top -- 56 bot"); diagonal_pens.push(red);

string arms[], arm_ss[], arm_labels[];
arms.push("_L"); arm_ss.push("L"); arm_labels.push("left arm");
arms.push("_R"); arm_ss.push("R"); arm_labels.push("right arm");
arms.push(""); arm_ss.push(""); arm_labels.push("double arm");

xSizeDef = 12cm;
//xTicksDef = LeftTicks(Step=1, step=0.5);

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int ai : arms.keys)
{
	NewPad(false);
	label("{\SetFontSizesXX " + arm_labels[ai] + " arm}");
}

//----------------------------------------------------------------------------------------------------

frame f_legend;

for (int dsi : datasets.keys)
{
	NewRow();

	NewPad(false);
	label("{\SetFontSizesXX " + datasets[dsi] + "}");

	for (int ai : arms.keys)
	{
		NewPad("$\th_y^{*"+arm_ss[ai]+"}\ung{\mu rad}$", "mode of~$\th_x^{*"+arm_ss[ai]+"}$");
		for (int dgni : diagonals.keys)
		{
			TF1_x_min = -inf;
			TF1_x_max = +inf;

			pen p = StdPen(dgni+1);

			string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";

			string base = "selected - angles/g_mode_th_x"+arms[ai]+"_vs_th_y"+arms[ai];

			draw(scale(1e6, 1e6), RootGetObject(f, base), "p", p, mCi+2pt+p, diagonal_labels[dgni]);
			draw(scale(1e6, 1e6), RootGetObject(f, base + "|pol1"), p + dashed);
		}

		limits((-100, -30), (100, 30), Crop);
	}
	
	f_legend = BuildLegend();

	NewPad(false);
	add(f_legend);
}

GShipout(vSkip=0mm);
