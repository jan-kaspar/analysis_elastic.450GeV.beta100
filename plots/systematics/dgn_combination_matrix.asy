import root;
import pad_layout;
import common_code;
include "../common.asy";

AddAllModes();

string f = topDir + "studies/systematics/matrix.root";

string binning = "sb1";

string collection = "all-but-norm";

real z_t_maxs[], z_t_Steps[], z_t_steps[], z_e_maxs[], z_e_Steps[], z_e_steps[];
z_t_maxs.push(0.004); z_t_Steps.push(0.002); z_t_steps.push(0.001); z_e_maxs.push(0.02); z_e_Steps.push(0.005); z_e_steps.push(0.001);
//z_t_maxs.push(0.2); z_t_Steps.push(0.05); z_t_steps.push(0.01); z_e_maxs.push(0.02); z_e_Steps.push(0.005); z_e_steps.push(0.001);
z_t_maxs.push(0.03); z_t_Steps.push(0.01); z_t_steps.push(0.05); z_e_maxs.push(0.04); z_e_Steps.push(0.01); z_e_steps.push(0.005);

TH2_palette = Gradient(blue, heavygreen, yellow, red);

//----------------------------------------------------------------------------------------------------

for (int zi : z_t_maxs.keys)
{
	NewPad("$|t|\ung{GeV^2}$", "$|t|\ung{GeV^2}$");

	real t_Step = z_t_Steps[zi];
	real t_step = z_t_steps[zi];

	real t_min = 0;
	real t_max = z_t_maxs[zi];

	TH2_x_max = t_max;
	TH2_y_max = t_max;

	draw(RootGetObject(f, "matrices/"+collection+"/"+binning+"/h_corr_mat"));

	currentpad.xTicks = LeftTicks(t_Step, t_step);
	currentpad.yTicks = RightTicks(t_Step, t_step);

	limits((0, 0), (t_max, t_max), Crop);
}

GShipout();
