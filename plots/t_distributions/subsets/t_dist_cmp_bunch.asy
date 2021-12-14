import root;
import pad_layout;
include "../../common.asy";

string dataset_ref = "data/all-good/Totem1/default/";

string dataset_pattern = "data/all-good/Totem1/bunch_<BUNCH>";

string bunches[];
bunches.push("11");
bunches.push("520");
bunches.push("1019");
bunches.push("1541");
bunches.push("2067");
bunches.push("2555");

string diagonals[], diagLabels[];
diagonals.push("45b_56t"); diagLabels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); diagLabels.push("45 top -- 56 bot");

string binning = "sb1";

//----------------------------------------------------------------------------------------------------

for (int bi : bunches.keys)
{
	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	scale(Linear, Log);

	for (int dgni : diagonals.keys)
	{
		string diagonal = diagonals[dgni];
		pen p = StdPen(dgni + 1);

		string on = "normalization/" + binning + "/h_t_normalized";

		string f = topDir + replace(dataset_pattern, "<BUNCH>", bunches[bi]) + "/distributions_" + diagonal + ".root";
		draw(RootGetObject(f, on), "d0,eb", p, "bunch " + bunches[bi]);

		string f = topDir + replace(dataset_ref, "<BUNCH>", bunches[bi]) + "/distributions_" + diagonal + ".root";
		draw(RootGetObject(f, on), "d0,vl", p+dashed, "ref");
	}

	//limits((0, 1e-3), (1.1, 1e3), Crop);

	AttachLegend();
}
