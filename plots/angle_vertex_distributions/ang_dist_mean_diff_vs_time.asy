import root;
import pad_layout;
include "../common.asy";
include "../run_info.asy";

string datasets[], dataset_fills[];
//datasets.push("data/fill7280/Totem1"); dataset_fills.push("7280");
datasets.push("data/fill7281/Totem1"); dataset_fills.push("7281");
//datasets.push("data/fill7282/Totem1"); dataset_fills.push("7282");
//datasets.push("data/fill7283/Totem1"); dataset_fills.push("7283");
//datasets.push("data/fill7284/Totem1"); dataset_fills.push("7284");
//datasets.push("data/fill7285/Totem1"); dataset_fills.push("7285");
//datasets.push("data/fill7286/Totem1"); dataset_fills.push("7286");
//datasets.push("data/fill7287/Totem1"); dataset_fills.push("7287");
//datasets.push("data/fill7288/Totem1"); dataset_fills.push("7288");
datasets.push("data/fill7289/Totem1"); dataset_fills.push("7289");
//datasets.push("data/fill7290/Totem1"); dataset_fills.push("7290");
datasets.push("data/fill7291/Totem1"); dataset_fills.push("7291");

string diagonals[], diagonal_labels[];
diagonals.push("45b_56t"); diagonal_labels.push("45 bot -- 56 top");
diagonals.push("45t_56b"); diagonal_labels.push("45 top -- 56 bot");

xTicksDef = LeftTicks(Step = 1, step = 6);

//----------------------------------------------------------------------------------------------------

void SetPadWidth()
{
	real factorHoursToSize = 4cm / 3;

	real timespan = currentpicture.userMax2().x - currentpicture.userMin2().x;
	currentpad.xSize = timespan * factorHoursToSize;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_x^*$}\hbox{220-210 difference}\hbox{left arm}}");

for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{220-210} \th_x^{*L}\ung{\mu rad}$");
	real y_min = -5., y_max = +5.;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/p_diffFN_th_x_L_vs_time"), "eb,d0", StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}

//----------------------------------------------------------------------------------------------------

NewRow();

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_x^*$}\hbox{220-210 difference}\hbox{right arm}}");

for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{220-210} \th_x^{*R}\ung{\mu rad}$");
	real y_min = -5., y_max = +5.;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/p_diffFN_th_x_R_vs_time"), "eb,d0", StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}

//----------------------------------------------------------------------------------------------------
NewRow();

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_x^*$}\hbox{right -- left difference}}");

for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{R-L} \th_x^{*}\ung{\mu rad}$");
	real y_min = -50, y_max = +50;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/p_diffRL_th_x_vs_time"), "eb,d0", StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}

//----------------------------------------------------------------------------------------------------
NewRow();

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_y^*$}\hbox{220-210 difference}\hbox{left arm}}");

for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{220-210} \th_y^{*L}\ung{\mu rad}$");
	real y_min = -1., y_max = +1.;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/p_diffFN_th_y_L_vs_time"), "eb,d0", StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}

//----------------------------------------------------------------------------------------------------

NewRow();

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_y^*$}\hbox{220-210 difference}\hbox{right arm}}");

for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{220-210} \th_y^{*R}\ung{\mu rad}$");
	real y_min = -1., y_max = +1.;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/p_diffFN_th_y_R_vs_time"), "eb,d0", StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}

//----------------------------------------------------------------------------------------------------
NewRow();

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_y^*$}\hbox{right -- left difference}}");

for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{R-L} \th_y^{*}\ung{\mu rad}$");
	real y_min = -5, y_max = +5;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/p_diffRL_th_y_vs_time"), "eb,d0", StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}

//----------------------------------------------------------------------------------------------------
NewRow();

NewPad(false);
label("\vbox{\SetFontSizesXX\hbox{$\th_y^*$}\hbox{right -- left difference}\hbox{extrapolated to $\th_y^* = 0$}}");

TGraph_errorBar = None;
for (int dsi : datasets.keys)
{
	NewPad("time $\ung{h}$", "$\De^{R-L} \th_y^{*}\ung{\mu rad}$");
	real y_min = -10., y_max = +10;

	DrawRunBands(dataset_fills[dsi], y_min, y_max);

	for (int dgni : diagonals.keys)
	{
		string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";
		draw(scale(1/3600, 1e6), RootGetObject(f, "time dependences/g_ext_diffRL_th_y_vs_time"), "p", StdPen(dgni+1), mCi+2pt+StdPen(dgni+1));
	}

	ylimits(y_min, y_max, Crop);

	SetPadWidth();
}
