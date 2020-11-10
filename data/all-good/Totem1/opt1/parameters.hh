#define USE_INIT_ADDITIONAL

#include "../../parameters.hh"

void Init_additional()
{
	anal.vtx_x_min = -0.5;
	anal.vtx_x_max = +0.5;

	if (diagonal == d45b_56t)
	{
		anal.fc_G = FiducialCut({{-338E-6, 32E-6}, {50E-6, 32E-6}, {100E-6, 45E-6}, {101E-6, 80E-6}, {100E-6, 110E-6}, {-310E-6, 110E-6}, {-385E-6, 60E-6}});
	}

	if (diagonal == d45t_56b)
	{
		anal.fc_G = FiducialCut({{-50E-6, 32E-6}, {-100E-6, 35E-6}, {-101E-6, 80E-6}, {-100E-6, 110E-6}, {315E-6, 110E-6}, {355E-6, 95E-6}, {375E-6, 43E-6}, {330E-6, 32E-6}});
	}
}
