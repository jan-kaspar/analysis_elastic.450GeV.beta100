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
currentpad.xTicks = LeftTicks(0.01, 0.005);
currentpad.yTicks = RightTicks(0.005, 0.001);

AddToLegend("<{\it resolution considerations:}");
draw(scale(1, 1), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), red+longdashed, "1 smearing sigma");
draw(scale(1, 2), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), blue+longdashed, "2 smearing sigma");
draw(scale(1, 3), RootGetObject(topDir+"binning/generators.root", "g_rms_t"), heavygreen+longdashed, "3 smearing sigma");

AddToLegend("<{\it fixed statistical uncertainty, " + dataset + ":}");

draw(RootGetObject(topDir+"binning/generators.root", "g_bs_stat_unc_30"), red+dashed, "$30\un{\%}$");
draw(RootGetObject(topDir+"binning/generators.root", "g_bs_stat_unc_20"), blue+dashed, "$20\un{\%}$");
draw(RootGetObject(topDir+"binning/generators.root", "g_bs_stat_unc_10"), heavygreen+dashed, "$10\un{\%}$");

AddToLegend("<{\it binnings in analysis:}");

for (int bi : binnings.keys)
{
	pen p = StdPen(bi);
	draw(RootGetObject(topDir + dataset + "/distributions_45b_56t.root", "binning/g_binning_"+binnings[bi]), "p,l,d0", p+0.2pt, mCi+0.8pt+p, binnings[bi]);
}

limits((0, 0), (0.04, 0.01), Crop);

/*
for (real x = 0; x <= 2.0; x += 0.3)
	yaxis(XEquals(x, false), dotted);

for (real y = 0; y <= 0.12; y += 0.01)
	xaxis(YEquals(y, false), dotted);
*/

frame f_legend = BuildLegend();

NewPad(false);
add(shift(0, 100)*f_legend);
