import root;
import pad_layout;
include "../../common.asy";

string topDir = "../../../acceptance_tests/";

string rows[] = {
	"simulations/<t_max>,1E8,uncorr/seed1/validation_with_mc.root",
	"simulations/<t_max>,1E8,corr/seed1/validation_with_mc.root",
};

//----------------------------------------------------------------------------------------------------

void PlotAll(string f, string binning)
{
	draw(RootGetObject(f, binning + "/h_t_tr"), "eb", blue, "el.~simu.");
	draw(RootGetObject(f, binning + "/h_t_re_no_acc"), "eb", heavygreen, "el.~simu.~+ smearing");
	draw(RootGetObject(f, binning + "/h_t_re_acc_phi"), "eb", black, "el.~simu.~+ smearing + fid.~cut (phi) + acc.~corr (phi)");
	draw(RootGetObject(f, binning + "/h_t_re_acc"), "eb", red, "el.~simu.~+ smearing + fid.~cut (all) + acc.~corr (all)");
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

	string f = topDir + replace(row, "<t_max>", "0.045");
	string binning = "eb";
	
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{a.u.}$");
	scale(Linear, Log);
	PlotAll(f, binning);
	limits((0, 1e8), (0.04, 1e11), Crop);

	
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{a.u.}$");
	scale(Linear, Log);
	PlotAll(f, binning);
	limits((0, 1e8), (0.003, 1e11), Crop);

	AttachLegend(NW, NE);
}
