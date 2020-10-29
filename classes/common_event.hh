#ifndef _common_event_hh_
#define _common_event_hh_

#include "common_alignment.hh"

// TODO: clean
/*
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>

#include "TGraph.h"
#include "TFile.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TMatrixDSymEigen.h"
#include "TRandom2.h"
*/

using namespace std;

//----------------------------------------------------------------------------------------------------

struct UnitHitData
{
	// validity flag
	unsigned int v;

	// hit position in mm
	double x, y;

	UnitHitData() : v(0), x(0.), y(0.) {}

	void operator += (const UnitHitData &add)
	{
		x += add.x;
		y += add.y;
	}
};

//----------------------------------------------------------------------------------------------------

struct HitData
{
	UnitHitData L_1_F, L_2_F /*, L_2_N, L_2_F*/;
	UnitHitData R_1_F, R_2_F /*, R_2_N, R_2_F*/;


	void operator += (const HitData &add)
	{
		L_1_F += add.L_1_F;
		L_2_F += add.L_2_F;

		R_1_F += add.R_1_F;
		R_2_F += add.R_2_F;
	}

	HitData ApplyAlignment(const AlignmentData &al) const
	{
		HitData r;

		r.L_2_F.x = L_2_F.x - al.a_L_2_F * L_2_F.y - al.b_L_2_F; r.L_2_F.y = L_2_F.y - al.c_L_2_F;
		r.L_1_F.x = L_1_F.x - al.a_L_1_F * L_1_F.y - al.b_L_1_F; r.L_1_F.y = L_1_F.y - al.c_L_1_F;

		r.R_1_F.x = R_1_F.x - al.a_R_1_F * R_1_F.y - al.b_R_1_F; r.R_1_F.y = R_1_F.y - al.c_R_1_F;
		r.R_2_F.x = R_2_F.x - al.a_R_2_F * R_2_F.y - al.b_R_2_F; r.R_2_F.y = R_2_F.y - al.c_R_2_F;

		return r;
	}

	// TODO: remove hard-coded z positions
	/*
	HitData ApplyInterpolatedAlignment(const AlignmentData &a, double sN, double sF) const
	{
		AlignmentData a_int = a.Interpolate(214.628, 220.000, sN, sF);

		return ApplyAlignment(a_int);
	}
	*/
};

//----------------------------------------------------------------------------------------------------

struct EventRed
{
	unsigned int lumi_section;
	unsigned int timestamp;
	unsigned int run_num, bunch_num, event_num;
	//unsigned int trigger_num;
	//unsigned int trigger_bits;

	// vertical RPs
	HitData h;

	//HitData hH;	// horizontal RPs
};

#endif