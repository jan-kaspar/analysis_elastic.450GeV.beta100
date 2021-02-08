import root;
import pad_layout;
include "../run_info.asy";
include "../common.asy";

string fills[], datasets[];
fills.push("7280"); datasets.push("data/fill7280/Totem1");
fills.push("7281"); datasets.push("data/fill7281/Totem1");
fills.push("7282"); datasets.push("data/fill7282/Totem1");
fills.push("7283"); datasets.push("data/fill7283/Totem1");
fills.push("7284"); datasets.push("data/fill7284/Totem1");
fills.push("7285"); datasets.push("data/fill7285/Totem1");
//fills.push("7286"); datasets.push("data/fill7286/Totem1");
//fills.push("7287"); datasets.push("data/fill7287/Totem1");
//fills.push("7288"); datasets.push("data/fill7288/Totem1");
fills.push("7289"); datasets.push("data/fill7289/Totem1");
//fills.push("7290"); datasets.push("data/fill7290/Totem1");
fills.push("7291"); datasets.push("data/fill7291/Totem1");

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };
pen dgn_pens[] = { blue, red };

string cuts[], c_units[];
real c_scales[];
real c_rms_min[], c_rms_max[];
cuts.push("1"); c_units.push("\mu rad"); c_scales.push(1e6); c_rms_min.push(20.); c_rms_max.push(60.);
cuts.push("2"); c_units.push("\mu rad"); c_scales.push(1e6); c_rms_min.push(5); c_rms_max.push(12);

cuts.push("5"); c_units.push("mm"); c_scales.push(1); c_rms_min.push(0.05); c_rms_max.push(0.10);
cuts.push("6"); c_units.push("mm"); c_scales.push(1); c_rms_min.push(0.05); c_rms_max.push(0.10);

cuts.push("7"); c_units.push("mm"); c_scales.push(1); c_rms_min.push(0.4); c_rms_max.push(0.7);
cuts.push("8"); c_units.push("mm"); c_scales.push(1); c_rms_min.push(2.0); c_rms_max.push(3.5);

cuts.push("9"); c_units.push("mm"); c_scales.push(1); c_rms_min.push(0.10); c_rms_max.push(0.20);
cuts.push("10"); c_units.push("mm"); c_scales.push(1); c_rms_min.push(0.10); c_rms_max.push(0.20);

string quantities[], q_options[], q_labels[];
//quantities.push("p_cq_time"); q_options.push("eb,d0"); q_labels.push("mean vs.~time");
quantities.push("g_cq_RMS"); q_options.push("p,d0"); q_labels.push("RMS vs.~time");

xSizeDef = 10cm;
ySizeDef = 6cm;

xTicksDef = LeftTicks(1., 0.5);

TGraph_errorBar = None;

//TGraph_reducePoints = 10;

//----------------------------------------------------------------------------------------------------

void SetPadWidth()
{
	real factorHoursToSize = 6cm / 3;

	real timespan = currentpicture.userMax2().x - currentpicture.userMin2().x;
	currentpad.xSize = timespan * factorHoursToSize;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

for (int ci : cuts.keys)
{
	for (int qi : quantities.keys)
	{
		NewRow();

		NewPad(false);
		label("{\SetFontSizesXX\vtop{\hbox{cut " + cuts[ci] + ":}\hbox{" + q_labels[qi] + "}}}");

		for (int dsi : datasets.keys)
		{
			NewPad("time $\ung{h}$", "$\ung{" + c_units[ci] + "}$");
			//currentpad.yTicks = RightTicks(1., 0.2);
			//real y_min = -3, y_max = +2;
			
			if (quantities[qi] == "g_cq_RMS")
				DrawRunBands(fills[dsi], c_rms_min[ci], c_rms_max[ci]);
		
			for (int dgni : diagonals.keys)
			{
				string f = topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root";

				RootObject obj = RootGetObject(f, "elastic cuts/cut " + cuts[ci] + "/" + quantities[qi] + cuts[ci]);

				if (obj.InheritsFrom("TGraph"))
					draw(swToHours*scale(1, c_scales[ci]), obj, q_options[qi], dgn_pens[dgni], mCi+2pt+dgn_pens[dgni], dgn_labels[dgni]);
				else
					draw(swToHours*scale(1, c_scales[ci]), obj, q_options[qi], dgn_pens[dgni], dgn_labels[dgni]);

				string obj_name_par = "elastic cuts/cut " + cuts[ci] + "/g_cut_parameters";
				RootObject obj_par = RootGetObject(f, obj_name_par);
				real ax[] = {0}, ay[] = {0};
				obj_par.vExec("GetPoint", 0, ax, ay); real cca = ay[0];
				obj_par.vExec("GetPoint", 1, ax, ay); real ccb = ay[0];
				obj_par.vExec("GetPoint", 2, ax, ay); real ccc = ay[0];
				obj_par.vExec("GetPoint", 3, ax, ay); real csi = ay[0];
				obj_par.vExec("GetPoint", 4, ax, ay); real n_si = ay[0];
		
				if (quantities[qi] == "g_cq_RMS")
				{
					xaxis(YEquals(csi * c_scales[ci], false), dgn_pens[dgni]+1pt+dashed);
				}
			}

			if (quantities[qi] == "g_cq_RMS")
			{
				ylimits(c_rms_min[ci], c_rms_max[ci], Crop);
			}
		
			SetPadWidth();
		}
	}
}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

frame f_leg = BuildLegend();

NewRow();

NewPad(false);
attach(f_leg);


GShipout(vSkip=0mm);
