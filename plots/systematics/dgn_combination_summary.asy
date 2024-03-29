import root;
import pad_layout;
import common_code;
include "../common.asy";

string f = topDir + "studies/systematics/matrix.root";

string binning = "sb1";

string objects[] = {
//	"input/45b_56t/<binning>",
//	"input/45t_56b/<binning>",
	"combined/<binning>/combination0",
	"combined/<binning>/combination1",
};

string object_labels[] = {
//	"45b-56t",
//	"45t-56b",
	"dgn. combination",
	"2nd dgn. combination",
};

string z_labels[];
real z_t_maxs[], z_t_Steps[], z_t_steps[], z_e_maxs[], z_e_Steps[], z_e_steps[];
z_t_maxs.push(0.004); z_t_Steps.push(0.002); z_t_steps.push(0.001); z_e_maxs.push(0.10); z_e_Steps.push(0.02); z_e_steps.push(0.01); z_labels.push("low $|t|$ zoom");
z_t_maxs.push(0.03); z_t_Steps.push(0.01); z_t_steps.push(0.05); z_e_maxs.push(0.10); z_e_Steps.push(0.02); z_e_steps.push(0.01); z_labels.push("full $|t|$ range");

//----------------------------------------------------------------------------------------------------

void PlotMultipleModes()
{
	int ci = 0;

	for (int mi : modes.keys)
	{
		for (int oi : objects.keys)
		{
			string pth = "contributions/" + modes[mi].mc_tag + "/" + replace(objects[oi], "<binning>", binning);
			RootObject obj = RootGetObject(f, pth, error=false);
			if (obj.valid)
			{
				draw(scale(1, 100), obj, "vl,d0", StdPen(ci+1), modes[mi].label + " ("+ replace(object_labels[oi], "_", "\_") + ")");
				++ci;
			}
		}
	}

	pen p_envelope = black+1pt;
	draw(scale(1, +100), RootGetObject(f, "matrices/all-but-norm/"+binning+"/h_stddev"), "vl", p_envelope);
	draw(scale(1, -100), RootGetObject(f, "matrices/all-but-norm/"+binning+"/h_stddev"), "vl", p_envelope);
	AddToLegend("$\pm 1\un{\si}$ {\it envelope of uncertainties (without normalisation)}", p_envelope);
}

//----------------------------------------------------------------------------------------------------

void PlotOneRow()
{
	NewRow();

	frame f_legend;

	for (int zi : z_t_maxs.keys)
	{
		NewPad("$|t|\ung{GeV^2}$", "systematic effect$\ung{\%}$");

		PlotMultipleModes();

		real t_Step = z_t_Steps[zi];
		real t_step = z_t_steps[zi];
		real e_Step = z_e_Steps[zi] * 100;
		real e_step = z_e_steps[zi] * 100;

		real t_min = 0;
		real t_max = z_t_maxs[zi];
		real e_min = -z_e_maxs[zi] * 100;
		real e_max = z_e_maxs[zi] * 100;

		currentpad.xTicks = LeftTicks(t_Step, t_step);
		currentpad.yTicks = RightTicks(e_Step, e_step);

		limits((0, -e_max), (t_max, e_max), Crop);

		xaxis(YEquals(0, false), dashed);
		yaxis(XEquals(t_min_axis, false), dashed);

		f_legend = BuildLegend();
		currentpicture.legend.delete();
	}

	NewPad(false);
	//add(shift(0, 345) * f_legend);
	add(shift(0, +80) * f_legend);
}

//----------------------------------------------------------------------------------------------------

for (int zi : z_t_maxs.keys)
	NewPadLabel(z_labels[zi]);

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("sh-thx");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("sh-thy");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("tilt-", "beam-mom");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("sc-");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("eff-");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("dx-", "dy-");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("mx-", "my-", "unsmearing-");
PlotOneRow();

//----------------------------------------------------------------------------------------------------

AddAllModes();
FilterModes("bckg");
PlotOneRow();

GShipout(vSkip=0mm);
