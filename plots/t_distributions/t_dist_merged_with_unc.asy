import root;
import pad_layout;
include "../common.asy";

string dataset = "merged";
string diagonal = "combined";
string binning = "sb1";

string unc_file = topDir + "studies/systematics/matrix.root";
string unc_types[], unc_labels[];
pen unc_pens[];
//unc_types.push("all"); unc_pens.push(blue+opacity(0.5)); unc_labels.push("all");
unc_types.push("all-but-norm"); unc_pens.push(green); unc_labels.push("all except normalisation");

drawGridDef = true;

TH1_x_min = 2e-4;

//----------------------------------------------------------------------------------------------------

void DrawUncBand(RootObject h, RootObject relUnc, pen p)
{
	if (relUnc.InheritsFrom("TH1"))
	{
		guide g_u, g_b;

		for (int bi = 1; bi < relUnc.iExec("GetNbinsX"); ++bi)
		{
			real c = relUnc.rExec("GetBinCenter", bi);
			real w = relUnc.rExec("GetBinWidth", bi);
			real ru = relUnc.rExec("GetBinContent", bi);

			real v = h.rExec("GetBinContent", bi);

			g_u = g_u -- Scale((c-w/2, v*(1.+ru))) -- Scale((c+w/2, v*(1.+ru)));
			g_b = g_b -- Scale((c-w/2, v*(1.-ru))) -- Scale((c+w/2, v*(1.-ru)));

			//g_u = g_u -- Scale((c, v*(1.+ru)));
			//g_b = g_b -- Scale((c, v*(1.-ru)));
		}

		g_b = reverse(g_b);
		filldraw(g_u--g_b--cycle, p, nullpen);
	}
}

//----------------------------------------------------------------------------------------------------

void PlotEverything()
{
	RootObject h_dsdt = RootGetObject(topDir + "data/merged.root", binning + "/" + dataset + "/" + diagonal + "/h_dsdt");

	AddToLegend("<systematic uncertainties:");
	for (int ui : unc_types.keys)
	{
		RootObject relUnc = RootGetObject(unc_file, "matrices/" + unc_types[ui] + "/" + binning + "/h_stddev");
		DrawUncBand(h_dsdt, relUnc, unc_pens[ui]);
		AddToLegend(unc_labels[ui], mSq+6pt+unc_pens[ui]);
	}

	AddToLegend("<data with statistical uncertainties:");
	draw(h_dsdt, "d0,eb", red+0.8pt);
	AddToLegend("data", mPl+4pt+(red+0.8pt));
}

//----------------------------------------------------------------------------------------------------

NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$", 8cm, 6cm);
//scale(Linear, Log);

PlotEverything();

currentpad.xTicks = LeftTicks(0.01, 0.005);
limits((0, 1e2), (0.03, 2e3), Crop);

//----------------------------------------------------------------------------------------------------

NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$", 8cm, 6cm);

PlotEverything();

currentpad.xTicks = LeftTicks(0.001, 0.0005);
limits((0, 1e2), (0.005, 2e3), Crop);

AttachLegend();
