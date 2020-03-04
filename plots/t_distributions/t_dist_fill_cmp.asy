import root;
import pad_layout;

string topDir = "../../";

string datasets[], dataset_fills[];
datasets.push("DS-fill7280/Totem1"); dataset_fills.push("7280");
datasets.push("DS-fill7281/Totem1"); dataset_fills.push("7281");
datasets.push("DS-fill7282/Totem1"); dataset_fills.push("7282");
datasets.push("DS-fill7283/Totem1"); dataset_fills.push("7283");
datasets.push("DS-fill7284/Totem1"); dataset_fills.push("7284");
datasets.push("DS-fill7285/Totem1"); dataset_fills.push("7285");
datasets.push("DS-fill7289/Totem1"); dataset_fills.push("7289");
datasets.push("DS-fill7291/Totem1"); dataset_fills.push("7291");

string diagonals[] = { "45b_56t", "45t_56b" };
string diagLabels[] = { "45 bot -- 56 top", "45 top -- 56 bot" };

string binning = "eb";

drawGridDef = true;

xSizeDef = 8cm;
ySizeDef = 8cm;

//----------------------------------------------------------------------------------------------------

for (int dsi : datasets.keys)
{
	//xTicksDef = LeftTicks(0.2, 0.1);

	NewPad("$|t|\ung{GeV^2}$", "$\d\si/\d t\ung{mb/GeV^2}$");
	scale(Linear, Log);

	for (int dgni : diagonals.keys)
	{
		pen p = StdPen(dgni + 1);
		string pth = "normalization/"+binning+"/h_t_normalized";
		//string pth = "normalization+unfolding/"+binning+"/h_t_normalized_unsmeared";
		draw(RootGetObject(topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root", pth),
			"d0,eb", p, diagLabels[dgni]);
	}

	limits((0, 4e1), (0.03, 1e4), Crop);

	AttachLegend(datasets[dsi]);
}
