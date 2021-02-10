import root;
import pad_layout;
include "../common.asy";
include "../run_info.asy";

string fills[], f_datasets[];
fills.push("7280"); f_datasets.push("data/fill7280/Totem1");
fills.push("7281"); f_datasets.push("data/fill7281/Totem1");
fills.push("7282"); f_datasets.push("data/fill7282/Totem1");
fills.push("7283"); f_datasets.push("data/fill7283/Totem1");
fills.push("7284"); f_datasets.push("data/fill7284/Totem1");
fills.push("7285"); f_datasets.push("data/fill7285/Totem1");
fills.push("7289"); f_datasets.push("data/fill7289/Totem1");
fills.push("7291"); f_datasets.push("data/fill7291/Totem1");

string quantities[], q_labels[];
pen q_pens[];
quantities.push("emit_b1_h"); q_labels.push("B1, horizontal"); q_pens.push(red);
quantities.push("emit_b1_v"); q_labels.push("B1, vertical"); q_pens.push(blue);
quantities.push("emit_b2_h"); q_labels.push("B2, horizontal"); q_pens.push(heavygreen);
quantities.push("emit_b2_v"); q_labels.push("B2, vertical"); q_pens.push(black);

xSizeDef = 40cm;
ySizeDef = 6cm;

xTicksDef = LeftTicks(2., 1.);

TGraph_reducePoints = 10;

TGraph_errorBar = None;

//----------------------------------------------------------------------------------------------------

NewPad("time from 11 Oct 2018$\ung{h}$", "normalised emittance$\ung{\mu m}$");

for (int fi : fills.keys)
{
	string f = topDir + f_datasets[fi] + "/process_timber.root";

	DrawFillBands(fills[fi], 0., 5., true);

	for (int qi : quantities.keys)
	{
		draw(scale(1./3600, 1e6), RootGetObject(f, "g_" + quantities[qi]), q_pens[qi]);
	}

	ylimits(0., 5., Crop);
}

for (int qi : quantities.keys)
	AddToLegend(q_labels[qi], q_pens[qi]);

AttachLegend(BuildLegend(NW), NE);
