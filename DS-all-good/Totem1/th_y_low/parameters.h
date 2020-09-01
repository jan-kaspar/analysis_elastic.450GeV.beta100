#define USE_INIT_ADDITIONAL

#include "../../parameters.h"

void Init_additional()
{
	if (diagonal == d45b_56t)
	{
		anal.fc_G = FiducialCut({{-338E-6, 32E-6}, {50E-6, 32E-6}, {250E-6, 42E-6}, {385E-6, 80E-6}, {-350E-6, 80E-6}, {-385E-6, 60E-6}});
	}

	if (diagonal == d45t_56b)
	{
		anal.fc_G = FiducialCut({{-50E-6, 32E-6}, {-250E-6, 42E-6}, {-365E-6, 80E-6}, {355E-6, 80E-6}, {375E-6, 43E-6}, {330E-6, 32E-6}});
	}
}
