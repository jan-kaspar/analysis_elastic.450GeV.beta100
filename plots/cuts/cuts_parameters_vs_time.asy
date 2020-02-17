import root;
import pad_layout;
include "../run_info.asy";

string topDir = "../../";

string fills[], datasets[];
//fills.push("7280"); datasets.push("DS-fill7280/Totem1");
fills.push("7281"); datasets.push("DS-fill7281/Totem1");
//fills.push("7282"); datasets.push("DS-fill7282/Totem1");
//fills.push("7283"); datasets.push("DS-fill7283/Totem1");
//fills.push("7284"); datasets.push("DS-fill7284/Totem1");
//fills.push("7285"); datasets.push("DS-fill7285/Totem1");
//fills.push("7286"); datasets.push("DS-fill7286/Totem1");
//fills.push("7287"); datasets.push("DS-fill7287/Totem1");
//fills.push("7288"); datasets.push("DS-fill7288/Totem1");
fills.push("7289"); datasets.push("DS-fill7289/Totem1");
//fills.push("7290"); datasets.push("DS-fill7290/Totem1");
fills.push("7291"); datasets.push("DS-fill7291/Totem1");

string diagonals[] = { "45b_56t", "45t_56b" };
string dgn_labels[] = { "45b -- 56t", "45t -- 56b" };
pen dgn_pens[] = { blue, red };

string cuts[], c_units[];
real c_scales[];
real c_rms_min[], c_rms_max[];
real c_sigmas_45b[], c_sigmas_45t[];
cuts.push("1"); c_units.push("\mu rad"); c_scales.push(1e6); c_sigmas_45b.push(40.); c_sigmas_45t.push(40.); c_rms_min.push(20.); c_rms_max.push(60.);
cuts.push("2"); c_units.push("\mu rad"); c_scales.push(1e6); c_sigmas_45b.push(9); c_sigmas_45t.push(9); c_rms_min.push(5); c_rms_max.push(12);

cuts.push("5"); c_units.push("mm"); c_scales.push(1); c_sigmas_45b.push(0.08); c_sigmas_45t.push(0.08); c_rms_min.push(0.05); c_rms_max.push(0.12);
cuts.push("6"); c_units.push("mm"); c_scales.push(1); c_sigmas_45b.push(0.08); c_sigmas_45t.push(0.08); c_rms_min.push(0.05); c_rms_max.push(0.12);

cuts.push("7"); c_units.push("mm"); c_scales.push(1); c_sigmas_45b.push(0.5); c_sigmas_45t.push(0.5); c_rms_min.push(0.3); c_rms_max.push(0.7);
cuts.push("8"); c_units.push("mm"); c_scales.push(1); c_sigmas_45b.push(3.); c_sigmas_45t.push(3.); c_rms_min.push(1.5); c_rms_max.push(4.5);

cuts.push("9"); c_units.push("mm"); c_scales.push(1); c_sigmas_45b.push(0.15); c_sigmas_45t.push(0.15); c_rms_min.push(0.10); c_rms_max.push(0.20);
cuts.push("10"); c_units.push("mm"); c_scales.push(1); c_sigmas_45b.push(0.15); c_sigmas_45t.push(0.15); c_rms_min.push(0.10); c_rms_max.push(0.20);

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
				RootObject obj = RootGetObject(topDir+datasets[dsi]+"/distributions_"+diagonals[dgni]+".root",
					"elastic cuts/cut " + cuts[ci] + "/" + quantities[qi] + cuts[ci]);

				if (obj.InheritsFrom("TGraph"))
					draw(swToHours*scale(1, c_scales[ci]), obj, q_options[qi], dgn_pens[dgni], mCi+2pt+dgn_pens[dgni], dgn_labels[dgni]);
				else
					draw(swToHours*scale(1, c_scales[ci]), obj, q_options[qi], dgn_pens[dgni], dgn_labels[dgni]);
		
				if (quantities[qi] == "g_cq_RMS")
				{
					real sigma = (diagonals[dgni] == "45b_56t") ? c_sigmas_45b[ci] : c_sigmas_45t[ci];
					xaxis(YEquals(sigma, false), dgn_pens[dgni]+1pt+dashed);
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
