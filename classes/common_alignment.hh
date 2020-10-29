#ifndef _common_alignment_hh_
#define _common_alignment_hh_

#include "TFile.h"
#include "TGraph.h"

#include <string>

// TODO: clean
/*
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>

#include "TFile.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TMatrixDSymEigen.h"
#include "TRandom2.h"
*/

using namespace std;

//----------------------------------------------------------------------------------------------------

struct AlignmentData
{
	//	a: xy coupling in rad
	//	b: x shift in mm
	//	c: y shift in mm
	double a_L_2_F, b_L_2_F, c_L_2_F;
	double a_L_1_F, b_L_1_F, c_L_1_F;

	double a_R_1_F, b_R_1_F, c_R_1_F;
	double a_R_2_F, b_R_2_F, c_R_2_F;

	AlignmentData()
	{
		a_L_2_F = b_L_2_F = c_L_2_F = 0.;
		a_L_1_F = b_L_1_F = c_L_1_F = 0.;

		a_R_1_F = b_R_1_F = c_R_1_F = 0.;
		a_R_2_F = b_R_2_F = c_R_2_F = 0.;
	}

	/*
	AlignmentData Interpolate(double s_N, double s_F, double s_NH, double s_FH) const
	{
		AlignmentData r;

		r.a_L_F = a_L_N + (a_L_F - a_L_N)/(s_F - s_N) * (s_FH - s_N); r.a_L_N = a_L_N + (a_L_F - a_L_N)/(s_F - s_N) * (s_NH - s_N);
		r.a_R_F = a_R_N + (a_R_F - a_R_N)/(s_F - s_N) * (s_FH - s_N); r.a_R_N = a_R_N + (a_R_F - a_R_N)/(s_F - s_N) * (s_NH - s_N);

		r.b_L_F = b_L_N + (b_L_F - b_L_N)/(s_F - s_N) * (s_FH - s_N); r.b_L_N = b_L_N + (b_L_F - b_L_N)/(s_F - s_N) * (s_NH - s_N);
		r.b_R_F = b_R_N + (b_R_F - b_R_N)/(s_F - s_N) * (s_FH - s_N); r.b_R_N = b_R_N + (b_R_F - b_R_N)/(s_F - s_N) * (s_NH - s_N);

		r.c_L_F = c_L_N + (c_L_F - c_L_N)/(s_F - s_N) * (s_FH - s_N); r.c_L_N = c_L_N + (c_L_F - c_L_N)/(s_F - s_N) * (s_NH - s_N);
		r.c_R_F = c_R_N + (c_R_F - c_R_N)/(s_F - s_N) * (s_FH - s_N); r.c_R_N = c_R_N + (c_R_F - c_R_N)/(s_F - s_N) * (s_NH - s_N);

		return r;
	}
	*/
};

//----------------------------------------------------------------------------------------------------

enum AlignmentType { atNone, atConstant, atTimeDependent };

struct AlignmentSource
{
	struct GraphSet
	{
		TGraph *L_2_F, *L_1_F, *R_1_F, *R_2_F;
		GraphSet() : L_2_F(NULL), L_1_F(NULL), R_1_F(NULL), R_2_F(NULL)
		{
		}
	} gs_a, gs_b, gs_c;

	AlignmentData cnst;

	AlignmentType type_a, type_b, type_c;
	string src_a, src_b, src_c;

	AlignmentSource() : type_a(atNone), type_b(atNone), type_c(atNone)
	{
	}

	void SetAlignmentA(AlignmentType t, const string &fn = "")
	{
		type_a = t;
		src_a = fn;
	}

	void SetAlignmentB(AlignmentType t, const string &fn = "")
	{
		type_b = t;
		src_b = fn;
	}

	void SetAlignmentC(AlignmentType t, const string &fn = "")
	{
		type_c = t;
		src_c = fn;
	}

	void InitOne(const string label, AlignmentType t, const string &fn, GraphSet &gs, const string &obj)
	{
		printf(">> AlignmentSource::InitOne > alignment `%s': type %u\n", label.c_str(), t);

		if (t == atTimeDependent)
		{
			TFile *alF = new TFile(fn.c_str());

			if (alF->IsZombie())
			{
				printf("\tERROR: cannot open file with alignment graphs.\n");
				delete alF;
				return;
			}

			TGraph *g_L_2_F = (TGraph *) alF->Get(( string("L_2_F/") + obj).c_str() );
			TGraph *g_L_1_F = (TGraph *) alF->Get(( string("L_1_F/") + obj).c_str() );

			TGraph *g_R_1_F = (TGraph *) alF->Get(( string("R_1_F/") + obj).c_str() );
			TGraph *g_R_2_F = (TGraph *) alF->Get(( string("R_2_F/") + obj).c_str() );

			if (g_L_2_F && g_L_1_F && g_R_1_F && g_R_2_F)
			{
				printf("\talignment graphs successfully loaded\n");
			} else {
				printf("\tERROR: unable to load some alignment graphs\n");
				delete alF;
				return;
			}

			gs.L_2_F = new TGraph(*g_L_2_F);
			gs.L_1_F = new TGraph(*g_L_1_F);

			gs.R_1_F = new TGraph(*g_R_1_F);
			gs.R_2_F = new TGraph(*g_R_2_F);

			delete alF;
		}
	}

	void Init()
	{
		printf(">> AlignmentSource::Init\n");
		InitOne("a", type_a, src_a, gs_a, "a_fit");
		InitOne("b", type_b, src_b, gs_b, "b_fit");
		InitOne("c", type_c, src_c, gs_c, "c_fit");
	}

	AlignmentData Eval(double timestamp) const
	{
		AlignmentData d;

		// a
		if (type_a == atNone)
		{
			d.a_L_2_F = 0.;
			d.a_L_1_F = 0.;

			d.a_R_1_F = 0.;
			d.a_R_2_F = 0.;
		}

		if (type_a == atConstant)
		{
			d.a_L_2_F = cnst.a_L_2_F;
			d.a_L_1_F = cnst.a_L_1_F;

			d.a_R_1_F = cnst.a_R_1_F;
			d.a_R_2_F = cnst.a_R_2_F;
		}

		if (type_a == atTimeDependent)
		{
			d.a_L_2_F = gs_a.L_2_F->Eval(timestamp)*1E-3;
			d.a_L_1_F = gs_a.L_1_F->Eval(timestamp)*1E-3;

			d.a_R_1_F = gs_a.R_1_F->Eval(timestamp)*1E-3;
			d.a_R_2_F = gs_a.R_2_F->Eval(timestamp)*1E-3;
		}

		// b
		if (type_b == atNone)
		{
			d.b_L_2_F = 0.;
			d.b_L_1_F = 0.;

			d.b_R_1_F = 0.;
			d.b_R_2_F = 0.;
		}

		if (type_b == atConstant)
		{
			d.b_L_2_F = cnst.b_L_2_F;
			d.b_L_1_F = cnst.b_L_1_F;

			d.b_R_1_F = cnst.b_R_1_F;
			d.b_R_2_F = cnst.b_R_2_F;
		}

		if (type_b == atTimeDependent)
		{
			d.b_L_2_F = gs_b.L_2_F->Eval(timestamp)*1E-3;
			d.b_L_1_F = gs_b.L_1_F->Eval(timestamp)*1E-3;

			d.b_R_1_F = gs_b.R_1_F->Eval(timestamp)*1E-3;
			d.b_R_2_F = gs_b.R_2_F->Eval(timestamp)*1E-3;
		}

		// c
		if (type_c == atNone)
		{
			d.c_L_2_F = 0.;
			d.c_L_1_F = 0.;

			d.c_R_1_F = 0.;
			d.c_R_2_F = 0.;
		}

		if (type_c == atConstant)
		{
			d.c_L_2_F = cnst.c_L_2_F;
			d.c_L_1_F = cnst.c_L_1_F;

			d.c_R_1_F = cnst.c_R_1_F;
			d.c_R_2_F = cnst.c_R_2_F;
		}

		if (type_c == atTimeDependent)
		{
			d.c_L_2_F = gs_c.L_2_F->Eval(timestamp)*1E-3;
			d.c_L_1_F = gs_c.L_1_F->Eval(timestamp)*1E-3;

			d.c_R_1_F = gs_c.R_1_F->Eval(timestamp)*1E-3;
			d.c_R_2_F = gs_c.R_2_F->Eval(timestamp)*1E-3;
		}

		return d;
	}
};

#endif