import root;
import pad_layout;

string topDir = "../../";

xSizeDef = 10cm;
ySizeDef = 8cm;

string dataset = "DS-fill7291/Totem1";

//----------------------------------------------------------------------------------------------------

string binnings[] = {
	"eb",
	//"ob-1-30-0.10",
	//"ob-2-20-0.20",
	//"ob-3-10-0.30",
};

//----------------------------------------------------------------------------------------------------

NewPad("$|t|\ung{GeV^2}$", "$t$ bin size$\ung{GeV^2}$");
scale(Linear, Log);

currentpad.xTicks = LeftTicks(0.01, 0.005);
//currentpad.yTicks = RightTicks(0.005, 0.001);

AddToLegend("<{\it resolution considerations:}");
/*
draw(scale(1, 1), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), red+longdashed, "1 smearing sigma");
draw(scale(1, 2), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), blue+longdashed, "2 smearing sigma");
draw(scale(1, 3), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), heavygreen+longdashed, "3 smearing sigma");
*/
draw(shift(0, log10(1)), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), red+longdashed, "1 smearing sigma");
draw(shift(0, log10(2)), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), blue+longdashed, "2 smearing sigma");
draw(shift(0, log10(3)), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), heavygreen+longdashed, "3 smearing sigma");

AddToLegend("<{\it fixed statistical uncertainty:}");
draw(RootGetObject(topDir+"binning/generators.root", "g_bs_stat_unc_0.020"), red+dashed, "$2\un{\%}$");
draw(RootGetObject(topDir+"binning/generators.root", "g_bs_stat_unc_0.010"), blue+dashed, "$1\un{\%}$");
draw(RootGetObject(topDir+"binning/generators.root", "g_bs_stat_unc_0.005"), heavygreen+dashed, "$0.5\un{\%}$");

AddToLegend("<{\it binnings in analysis:}");
for (int bi : binnings.keys)
{
	pen p = StdPen(bi);
	draw(RootGetObject(topDir + dataset + "/distributions_45b_56t.root", "binning/g_binning_"+binnings[bi]), "p,l,d0", p+0.2pt, mCi+0.8pt+p, binnings[bi]);
}

limits((0, 1e-4), (0.04, 0.01), Crop);

frame f_legend = BuildLegend();

NewPad(false);
add(shift(0, 100)*f_legend);