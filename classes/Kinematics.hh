#ifndef _Kinematics_hh_
#define _Kinematics_hh_

// TODO: clean
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

using namespace std;

//----------------------------------------------------------------------------------------------------

struct Kinematics
{
	double th_x_L_1_F, th_x_L_2_F, th_x_R_1_F, th_x_R_2_F, th_x_L, th_x_R, th_x;	//	rad
	double th_y_L_1_F, th_y_L_2_F, th_y_R_1_F, th_y_R_2_F, th_y_L, th_y_R, th_y;	//	rad

	double vtx_x_L_1_F, vtx_x_L_2_F, vtx_x_R_1_F, vtx_x_R_2_F, vtx_x_L, vtx_x_R, vtx_x;	// in mm
	double vtx_y_L_1_F, vtx_y_L_2_F, vtx_y_R_1_F, vtx_y_R_2_F, vtx_y_L, vtx_y_R, vtx_y;	// in mm

	double th;				// in rad
	double phi;				// in rad
	double t_x, t_y, t;		// in GeV^2

	Kinematics() : th_y(0.) {}

	void ThetasToTPhi(const Environment &env)
	{
		th = sqrt(th_x*th_x + th_y*th_y);
		t_x = env.p*env.p * th_x * th_x;
		t_y = env.p*env.p * th_y * th_y;
		t = t_x + t_y;
		phi = atan2(th_y, th_x);
	}

	void TPhiToThetas(const Environment &env)
	{
		th = sqrt(t) / env.p;
		th_x_L = th_x_R = th_x = th * cos(phi);
		th_y_L = th_y_R = th_y = th * sin(phi);

		t_x = t * cos(phi) * cos(phi);
		t_y = t * sin(phi) * sin(phi);
	}
};

#endif
