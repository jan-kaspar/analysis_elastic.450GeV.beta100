import root;
import pad_layout;
include "../../common.asy";

string topDir = "../../../acceptance_tests/";

string rows[] = {
	"simulations/0.045,1E8,uncorr/seed1/validation_with_mc.root",
	"simulations/0.045,1E8,corr/seed1/validation_with_mc.root",
};

string th_x_ranges[] = {
	"-5.0E-07_+5.0E-07", 
	"+1.0E-04_+1.0E-04", 
	"+2.0E-04_+2.0E-04", 
	"+3.0E-04_+3.0E-04", 
};

//----------------------------------------------------------------------------------------------------

NewPad(false);

for (string th_x_range : th_x_ranges)
{
	NewPad(false);
	label("$\th_x^*$ from " + replace(th_x_range, "_", " to "));
}

for (string row : rows)
{
	NewRow();

	NewPad(false);
	label(replace(row, "_", "\_"));

	string f = topDir + row;

	for (string th_x_range : th_x_ranges)
	{
		string dir = "th_x_ranges/" + th_x_range + "/";

		NewPad("$\theta^*_y\ung{\mu rad}$", "acceptance");
		draw(scale(1e6, 1), RootGetObject(f, dir + "h_th_ratio_cut_over_no_cut"), "eb", magenta);
		draw(scale(1e6, 1), RootGetObject(f, dir + "g_acc_smear_vs_th_y"), "l", black);
		
		limits((30, 0.4), (80, 1.1), Crop);
	}
	
	//yaxis(XEquals(t_min, false), dashed);
}

GShipout(vSkip=1mm);
