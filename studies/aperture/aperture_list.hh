#ifndef _aperture_list_hh_
#define _aperture_list_hh_

#include "apertures.hh"

#include <vector>
#include <string>
#include <map>

std::map<unsigned int, std::vector<Element>> elements;

void InitElements()
{
	elements[1] = {
		{ "MBCS2.1R5", 6.50E+00, { "RECTELLIPSE", 9.999999, 9.999999, 9.999999, 9.999999 }, { 1.00E+00, 6.50E+00, 1.00E+00, 6.50E+00 } },
		{ "BPMSW.1R5.B1", 2.16E+01, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { 1.00E+00, 2.16E+01, 1.00E+00, 2.16E+01 } },
		{ "BPMSW.1R5.B1_DOROS", 2.16E+01, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { 1.00E+00, 2.16E+01, 1.00E+00, 2.16E+01 } },
		{ "BPMWK.1R5", 2.16E+01, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { 1.00E+00, 2.16E+01, 1.00E+00, 2.16E+01 } },
		{ "BPMWF.A1R5.B1", 2.17E+01, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { 1.00E+00, 2.17E+01, 1.00E+00, 2.17E+01 } },
		{ "MQXA.1R5", 2.93E+01, { "RECTELLIPSE", 0.02385, 0.01895, 0.02385, 0.02385 }, { 8.76E-01, 2.62E+01, 1.13E+00, 3.26E+01 } },
		{ "MCBXH.1R5", 2.98E+01, { "RECTELLIPSE", 0.02385, 0.01895, 0.02385, 0.02385 }, { 8.57E-01, 2.62E+01, 1.15E+00, 3.36E+01 } },
		{ "MCBXV.1R5", 2.98E+01, { "RECTELLIPSE", 0.02385, 0.01895, 0.02385, 0.02385 }, { 8.57E-01, 2.62E+01, 1.15E+00, 3.36E+01 } },
		{ "BPMS.2R5.B1", 3.15E+01, { "RECTELLIPSE", 0.0301, 0.0301, 0.0301, 0.0301 }, { 7.93E-01, 2.62E+01, 1.22E+00, 3.71E+01 } },
		{ "MQXB.A2R5", 3.76E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 6.31E-01, 2.87E+01, 1.35E+00, 4.58E+01 } },
		{ "MCBXH.2R5", 3.80E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 6.24E-01, 2.92E+01, 1.35E+00, 4.61E+01 } },
		{ "MCBXV.2R5", 3.80E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 6.24E-01, 2.92E+01, 1.35E+00, 4.61E+01 } },
		{ "MQXB.B2R5", 4.41E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 5.90E-01, 3.76E+01, 1.21E+00, 4.56E+01 } },
		{ "MQSX.3R5", 4.67E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 6.05E-01, 4.31E+01, 1.08E+00, 4.31E+01 } },
		{ "MQXA.3R5", 5.33E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 5.55E-01, 5.00E+01, 9.13E-01, 4.28E+01 } },
		{ "MCBXH.3R5", 5.38E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 5.45E-01, 4.99E+01, 9.11E-01, 4.32E+01 } },
		{ "MCBXV.3R5", 5.38E+01, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { 5.45E-01, 4.99E+01, 9.11E-01, 4.32E+01 } },
		{ "BPMSY.4R5.B1", 5.83E+01, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { 4.52E-01, 4.96E+01, 8.93E-01, 4.73E+01 } },
		{ "MBXW.A4R5", 6.30E+01, { "RECTELLIPSE", 0.064, 0.0265, 0.064, 0.0265 }, { 3.54E-01, 4.93E+01, 8.74E-01, 5.16E+01 } },
		{ "MBXW.B4R5", 6.73E+01, { "RECTELLIPSE", 0.064, 0.0265, 0.064, 0.0265 }, { 2.65E-01, 4.90E+01, 8.56E-01, 5.54E+01 } },
		{ "MBXW.C4R5", 7.16E+01, { "RECTELLIPSE", 0.064, 0.0265, 0.064, 0.0265 }, { 1.76E-01, 4.87E+01, 8.39E-01, 5.93E+01 } },
		{ "MBXW.D4R5", 7.58E+01, { "RECTELLIPSE", 0.064, 0.0265, 0.064, 0.0265 }, { 8.78E-02, 4.84E+01, 8.22E-01, 6.31E+01 } },
		{ "MBXW.E4R5", 8.01E+01, { "RECTELLIPSE", 0.064, 0.0265, 0.064, 0.0265 }, { -9.45E-04, 4.81E+01, 8.04E-01, 6.70E+01 } },
		{ "MBXW.F4R5", 8.44E+01, { "RECTELLIPSE", 0.064, 0.0265, 0.064, 0.0265 }, { -8.97E-02, 4.78E+01, 7.87E-01, 7.09E+01 } },
		{ "TCL.4R5.B1", 1.51E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -1.47E+00, 4.32E+01, 5.18E-01, 1.31E+02 } },
		{ "BPMWB.4R5.B1", 1.51E+02, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { -1.48E+00, 4.31E+01, 5.15E-01, 1.31E+02 } },
		{ "MBRC.4R5.B1", 1.63E+02, { "RECTELLIPSE", 0.0313, 0.0264, 0.0313, 0.0313 }, { -1.72E+00, 4.23E+01, 4.68E-01, 1.42E+02 } },
		{ "MCBYV.A4R5.B1", 1.65E+02, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { -1.76E+00, 4.22E+01, 4.59E-01, 1.44E+02 } },
		{ "MCBYH.4R5.B1", 1.66E+02, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { -1.79E+00, 4.21E+01, 4.54E-01, 1.45E+02 } },
		{ "MCBYV.B4R5.B1", 1.67E+02, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { -1.82E+00, 4.20E+01, 4.49E-01, 1.46E+02 } },
		{ "MQY.4R5.B1", 1.71E+02, { "RECTELLIPSE", 0.0289, 0.024, 0.0289, 0.0289 }, { -1.94E+00, 4.26E+01, 4.24E-01, 1.46E+02 } },
		{ "BPMYA.4R5.B1", 1.72E+02, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { -1.98E+00, 4.30E+01, 4.15E-01, 1.46E+02 } },
		{ "TCL.5R5.B1", 1.85E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.53E+00, 4.86E+01, 2.97E-01, 1.34E+02 } },
		{ "BPM.5R5.B1", 1.93E+02, { "RECTELLIPSE", 0.024, 0.024, 0.024, 0.024 }, { -2.90E+00, 5.24E+01, 2.16E-01, 1.27E+02 } },
		{ "MQML.5R5.B1", 1.99E+02, { "RECTELLIPSE", 0.02255, 0.01765, 0.02255, 0.02255 }, { -2.93E+00, 5.11E+01, 1.78E-01, 1.31E+02 } },
		{ "MCBCH.5R5.B1", 2.00E+02, { "RECTELLIPSE", 0.02255, 0.01765, 0.02255, 0.02255 }, { -2.88E+00, 4.99E+01, 1.74E-01, 1.34E+02 } },
		{ "BPMWT.C6R5.B1", 2.03E+02, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { -2.74E+00, 4.63E+01, 1.62E-01, 1.43E+02 } },

		/*
		{ "XRPV.C6R5.B1", 2.03E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.73E+00, 4.60E+01, 1.62E-01, 1.44E+02 } },
		{ "XRPH.C6R5.B1", 2.04E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.71E+00, 4.55E+01, 1.60E-01, 1.45E+02 } },
		{ "XRPH.D6R5.B1", 2.13E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.31E+00, 3.57E+01, 1.28E-01, 1.71E+02 } },
		{ "XRPV.D6R5.B1", 2.13E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.29E+00, 3.52E+01, 1.26E-01, 1.72E+02 } },
		{ "BPMWT.D6R5.B1", 2.13E+02, { "RECTELLIPSE", 0.03, 0.03, 0.03, 0.03 }, { -2.28E+00, 3.49E+01, 1.25E-01, 1.73E+02 } },
		{ "BPMWT.A6R5.B1", 2.14E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.23E+00, 3.36E+01, 1.21E-01, 1.76E+02 } },
		{ "XRPV.A6R5.B1", 2.15E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.22E+00, 3.33E+01, 1.20E-01, 1.77E+02 } },
		{ "XRPH.A6R5.B1", 2.15E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.20E+00, 3.28E+01, 1.19E-01, 1.78E+02 } },
		{ "XRPH.E6R5.B1", 2.16E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.17E+00, 3.21E+01, 1.16E-01, 1.80E+02 } },
		{ "XRPH.B6R5.B1", 2.20E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -2.00E+00, 2.78E+01, 1.02E-01, 1.91E+02 } },
		{ "XRPV.B6R5.B1", 2.20E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -1.98E+00, 2.73E+01, 1.00E-01, 1.92E+02 } },
		{ "BPMWT.B6R5.B1", 2.20E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -1.97E+00, 2.70E+01, 9.96E-02, 1.93E+02 } },
		{ "TCL.6R5.B1", 2.22E+02, { "RECTELLIPSE", 0.04, 0.04, 0.04, 0.04 }, { -1.88E+00, 2.49E+01, 9.28E-02, 1.98E+02 } },
		*/

		{ "XRPV.B6R5.B1", 2.20E+02, { "RP", 5.5E-3, 0.04, 0.04, 0.04 }, { -1.98E+00, 2.73E+01, 1.00E-01, 1.92E+02 } },
	};

	// symmetric approximation

	elements[0] = elements[1];
}

#endif