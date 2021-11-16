import root;
import pad_layout;

string topDir = "../../";

string f = topDir + "data/fill7291/Totem1/distributions_45b_56t.root";

string f_tags[], f_labels[], f_shorts[];
f_tags.push("_L"); f_labels.push("left arm"); f_shorts.push("L");
f_tags.push("_R"); f_labels.push("right arm"); f_shorts.push("R");
f_tags.push("_G"); f_labels.push("both arms"); f_shorts.push("G");

string plots[], pl_x_labels[], pl_y_labels[];
plots.push("selected - vertex/<type>_vtx_x<tag>_vs_th_x<tag>"); pl_x_labels.push("$\th^*_x\ung{\mu rad}$"); pl_y_labels.push("$x^*\ung{mm}$");
plots.push("selected - vertex/<type>_vtx_y<tag>_vs_th_x<tag>"); pl_x_labels.push("$\th^*_x\ung{\mu rad}$"); pl_y_labels.push("$y^*\ung{mm}$");

plots.push("selected - vertex/<type>_vtx_x<tag>_vs_th_y<tag>"); pl_x_labels.push("$\th^*_y\ung{\mu rad}$"); pl_y_labels.push("$x^*\ung{mm}$");
plots.push("selected - vertex/<type>_vtx_y<tag>_vs_th_y<tag>"); pl_x_labels.push("$\th^*_y\ung{\mu rad}$"); pl_y_labels.push("$y^*\ung{mm}$");

for (int fi : f_tags.keys)
{
	NewRow();

	NewPadLabel(f_labels[fi]);

	for (int pli : plots.keys)
	{
		string plot = replace(plots[pli], "<tag>", f_tags[fi]);

		NewPad(pl_x_labels[pli], pl_y_labels[pli]);
		draw(scale(1e6, 1), RootGetObject(f, replace(plot, "<type>", "h2")));
		draw(scale(1e6, 1), RootGetObject(f, replace(plot, "<type>", "p")), "eb", black);
		draw(scale(1e6, 1), RootGetObject(f, replace(plot, "<type>", "p") + "|pol1"), cyan);
	}

	//GShipout("dist_2D_vtx_vs_ang" + f_tags[fi]);
}

GShipout(vSkip = 0mm);
