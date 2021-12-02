import root;
import pad_layout;

string topDir = "../";

string f = topDir + "analyze_tilts.root";

string datasets[];
//datasets.push("fill7291");
//datasets.push("fill7291-test");
//datasets.push("all-good:default");
datasets.push("all-good:tune");

string diagonals[], d_labels[];
diagonals.push("45b_56t"); d_labels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); d_labels.push("45 top -- 56 bot");

string arms[], a_labels[];
arms.push("L"); a_labels.push("x: left arm");
arms.push("R"); a_labels.push("x: right arm");

TGraph_errorBar = None;

transform xyswitch = (0, 0, 0, 1, 1, 0);

TH2_palette = Gradient(blue, heavygreen, yellow, red);

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int ai : arms.keys)
	NewPadLabel(a_labels[ai]);
NewPadLabel("xy (combined)");

for (int dsi : datasets.keys)
{
	for (int dgni : diagonals.keys)
	{
		NewRow();

		NewPadLabel(datasets[dsi] + ", " + d_labels[dgni]);

		for (int ai : arms.keys)
		{
			string base = datasets[dsi] + "/" + diagonals[dgni] + "/x/" + arms[ai];

			NewPad("$x^*\ung{mm}$", "$\th^*_x\ung{\mu rad}$");
			draw(scale(1, 1e6), RootGetObject(f, base + "/h2"));

			draw(scale(1, 1e6), RootGetObject(f, base + "/central/g_th_x_mode_vs_vtx_x"), "p", black);
			RootObject fit = RootGetObject(f, base + "/central/g_th_x_mode_vs_vtx_x|pol1");
			real sl = fit.rExec("GetParameter", 1), sl_unc = fit.rExec("GetParError", 1);
			string l = format("slope (B) = $(%#+.1f \pm", sl*1e6) + format(" %#.1f) \times 10^{-6}$", sl_unc*1e6);
			draw(scale(1, 1e6), fit, magenta, l);

			draw(scale(1, 1e6) * xyswitch, RootGetObject(f, base + "/band/g_vtx_x_mode_vs_th_x"), "p", black);
			RootObject fit = RootGetObject(f, base + "/band/g_vtx_x_mode_vs_th_x|pol1");
			real sl = fit.rExec("GetParameter", 1), sl_unc = fit.rExec("GetParError", 1);
			string l = format("slope (C) = $(%#+.1f \pm", sl) + format(" %#.1f)$", sl_unc);
			draw(scale(1, 1e6) * xyswitch, fit, cyan, l);

			AttachLegend(S, N);
		}

		{
			string base = datasets[dsi] + "/" + diagonals[dgni] + "/xy";

			NewPad("$\th^*_x\ung{\mu rad}$", "$\De^{R-L}\th^*_y\ung{\mu rad}$");
			draw(scale(1e6, 1e6), RootGetObject(f, base + "/h2"));

			draw(scale(1e6, 1e6), RootGetObject(f, base + "/g_mode_vs_th_x"), "p", black);
			RootObject fit = RootGetObject(f, base + "/g_mode_vs_th_x|pol1");
			real sl = fit.rExec("GetParameter", 1), sl_unc = fit.rExec("GetParError", 1);
			string l = format("slope (F) = $(%#+.1f \pm", sl*1e3) + format(" %#.1f) \times 10^{-3}$", sl_unc*1e3);
			draw(scale(1e6, 1e6), fit, magenta, l);

			AttachLegend(S, N);
		}
	}
}
