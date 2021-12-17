import root;
import pad_layout;
include "../common.asy";

string datasets[];
datasets.push("fill7280/Totem1");
datasets.push("fill7281/Totem1");
datasets.push("fill7282/Totem1");
datasets.push("fill7283/Totem1");
datasets.push("fill7284/Totem1");
datasets.push("fill7285/Totem1");
datasets.push("fill7289/Totem1");
datasets.push("fill7291/Totem1");

string diagonals[] = { "45b_56t", "45t_56b", "anti_45b_56b", "anti_45t_56t" };
string dgn_labels[] = { "45 bot -- 56 top", "45 top -- 56 bot", "45 bot -- 56 bot", "45 top -- 56 top" };

string q_tags[], q_paths[], q_axis_labels[];
real q_scales[], q_maxs[], q_Steps[], q_steps[];
q_tags.push("th_x"); q_paths.push("selected - angles/h_th_x"); q_axis_labels.push("$\th^*_x\ung{\mu rad}$"); q_scales.push(1e6); q_maxs.push(400); q_Steps.push(100); q_steps.push(50);
q_tags.push("th_y"); q_paths.push("selected - angles/h_th_y"); q_axis_labels.push("$\th^*_y\ung{\mu rad}$"); q_scales.push(1e6); q_maxs.push(150); q_Steps.push(30); q_steps.push(10);
q_tags.push("vtx_x"); q_paths.push("selected - vertex/h_vtx_x"); q_axis_labels.push("$x^*\ung{mm}$"); q_scales.push(1); q_maxs.push(2); q_Steps.push(0.5); q_steps.push(0.1);

xSizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int qi : q_tags.keys)
	NewPadLabel(replace(q_tags[qi], "_", "\_"));

for (int dsi : datasets.keys)
{
	NewRow();

	NewPadLabel(datasets[dsi]);

	for (int qi : q_tags.keys)
	{
		NewPad(q_axis_labels[qi]);
		scale(Linear, Log);
		currentpad.xTicks = LeftTicks(Step = q_Steps[qi], step = q_steps[qi]);

		for (int dgni : diagonals.keys)
		{
			string f = topDir + "data/" + datasets[dsi] + "/distributions_" + diagonals[dgni] + ".root";
			RootObject hist = RootGetObject(f, q_paths[qi]);
			draw(scale(q_scales[qi], 1), hist, "vl", StdPen(dgni+1), dgn_labels[dgni]);
		}
		
		xlimits(-q_maxs[qi], q_maxs[qi], Crop);
	}

	AttachLegend(NW, NE);
}

GShipout(vSkip=0mm);
