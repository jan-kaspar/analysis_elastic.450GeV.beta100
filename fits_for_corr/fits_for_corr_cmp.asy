import root;
import pad_layout;

NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");

scale(Linear, Log);

draw(RootGetObject("fit.root", "g_fit_1"), "l", black, "fit 1");

draw(RootGetObject("imported_fits.root", "g_fit_CH_HighBeta"), "l", red, "fit 2");
draw(RootGetObject("imported_fits.root", "g_fit_CH_BothBetas"), "l", blue, "fit 3");

limits((0, 8e1), (0.05, 1e5), Crop);

AttachLegend();
