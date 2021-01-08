import root;
import pad_layout;

string topDir = "../../../test/acceptance_code/";

string rows[] = {
	"simulations/0.04,1E8,uncorr/seed1/validation_with_mc.root",
	"simulations/0.04,1E8,corr/seed1/validation_with_mc.root",
};

string th_x_ranges[] = {
	"-5.0E-07_+5.0E-07", 
	"+1.0E-04_+1.0E-04", 
	"+2.0E-04_+2.0E-04", 
};

xSizeDef = 15cm;

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

		NewPad("$\theta^*_y\ung{\mu rad}$", "$\hbox{smearing + fiducial cuts + smearing corr.} \over \hbox{smearing}$");
		draw(scale(1e6, 1), RootGetObject(f, dir + "h_th_ratio_cut_corr_over_no_cut"), "eb", magenta);
		
		limits((30, 0.4), (140, 1.1), Crop);
	
		xaxis(YEquals(1, false), dashed);
	}
}

GShipout(vSkip=1mm);
