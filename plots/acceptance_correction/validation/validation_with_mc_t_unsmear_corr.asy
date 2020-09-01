import root;
import pad_layout;
include "../../common.asy";

string topDir = "../../../";

string rows[] = {
	"simulations/<t_max>,1E8,uncorr/seed1/validation_with_mc.root",
	"simulations/<t_max>,1E8,corr/seed1/validation_with_mc.root",
};

string ref_file = topDir + "DS-fill7291/Totem1/unfolding_cf_ni_45b_56t.root";
string ref_obj = "fit-1/g_t_corr";
TGraph_x_min = t_min;

//----------------------------------------------------------------------------------------------------

void PlotAll(string f, string binning)
{
	draw(RootGetObject(f, binning + "/h_t_ratio_tr_over_re_acc_phi"), "eb", blue, "fiducial cuts: phi only");
	draw(RootGetObject(f, binning + "/h_t_ratio_tr_over_re_acc"), "eb", red, "fiducial cuts: all");

	draw(RootGetObject(ref_file, ref_obj), "l", black, "dedicated calculation");
}

//----------------------------------------------------------------------------------------------------

for (string row : rows)
{
	NewRow();

	NewPad(false);
	string lab = replace(row, "_", "\_");
	lab = replace(lab, "<t\_max>", "$\langle t_{\rm max}\rangle$");
	label(lab);

	//--------------------
	
	string f = topDir + "acceptance_tests/" + replace(row, "<t_max>", "0.045");
	string binning = "eb";
	
	NewPad("$|t|\ung{GeV^2}$", "unsmearing correction (multiplicative)");
	//currentpad.yTicks = RightTicks(0.002, 0.001);
	PlotAll(f, binning);	
	limits((0, 0.90), (0.04, 1.10), Crop);

	AttachLegend(NW, NE);
}
