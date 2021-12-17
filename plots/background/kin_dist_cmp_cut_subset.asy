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

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };

string combinations[];
pen comb_pens[];
combinations.push("no_cuts"); comb_pens.push(gray);
combinations.push("cuts:1"); comb_pens.push(black);
combinations.push("cuts:1,2"); comb_pens.push(magenta);
combinations.push("cuts:1,2,5,6"); comb_pens.push(blue);
combinations.push("cuts:1,2,5,6,7,8"); comb_pens.push(heavygreen);
combinations.push("cuts:1,2,5,6,7,8,9,10"); comb_pens.push(red+1pt);

string q_tags[], q_paths[], q_axis_labels[];
real q_scales[], q_maxs[], q_Steps[], q_steps[];
q_tags.push("th_x"); q_paths.push("selected - angles/h_th_x"); q_axis_labels.push("$\th^*_x\ung{\mu rad}$"); q_scales.push(1e6); q_maxs.push(400); q_Steps.push(100); q_steps.push(50);
q_tags.push("th_y"); q_paths.push("selected - angles/h_th_y"); q_axis_labels.push("$\th^*_y\ung{\mu rad}$"); q_scales.push(1e6); q_maxs.push(150); q_Steps.push(30); q_steps.push(10);
q_tags.push("vtx_x"); q_paths.push("selected - vertex/h_vtx_x"); q_axis_labels.push("$x^*\ung{mm}$"); q_scales.push(1); q_maxs.push(2); q_Steps.push(0.5); q_steps.push(0.1);

xSizeDef = 10cm;

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int qi : q_tags.keys)
	NewPadLabel(replace(q_tags[qi], "_", "\_"));

for (int dsi : datasets.keys)
{
	for (int dgi : diagonals.keys)
	{
		NewRow();

		string dataset = datasets[dsi];
		string diagonal = diagonals[dgi];

		NewPad(false);
		label(replace("{\SetFontSizesXX\vbox{\hbox{"+dataset+"}\hbox{"+dgn_labels[dgi]+"}}}", "_", "\_"));

		for (int qi : q_tags.keys)
		{
			NewPad(q_axis_labels[qi]);
			currentpad.xTicks = LeftTicks(Step = q_Steps[qi], step = q_steps[qi]);

			for (int ci : combinations.keys)
			{
				string f = topDir + "studies/background/" + dataset + "/" + combinations[ci] + "/distributions_" + diagonal + ".root";
				string l = replace(combinations[ci], "_", "\_");
				draw(scale(q_scales[qi], 1), RootGetObject(f, q_paths[qi]), "vl", comb_pens[ci], l);
			}
			
			xlimits(-q_maxs[qi], q_maxs[qi], Crop);
		}

		AttachLegend(NW, NE);
	}
}

GShipout(vSkip=0mm);
