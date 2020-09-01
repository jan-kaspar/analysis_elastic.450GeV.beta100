#define USE_INIT_ADDITIONAL

#include "../../parameters.h"

void Init_additional()
{
	if (diagonal == d45b_56t)
	{
		//anal.fc_L = FiducialCut({{-338E-6, 34E-6}, {-105E-6, 34E-6}, {-104E-6, 80E-6}, {-105E-6, 125E-6}, {-280E-6, 127E-6}, {-380E-6, 60E-6}});
		//anal.fc_R = FiducialCut({{-338E-6, 34E-6}, {-105E-6, 34E-6}, {-104E-6, 80E-6}, {-105E-6, 125E-6}, {-280E-6, 127E-6}, {-380E-6, 60E-6}});
		anal.fc_G = FiducialCut({{-338E-6, 32E-6}, {-100E-6, 32E-6}, {-99E-6, 80E-6}, {-100E-6, 127E-6}, {-280E-6, 129E-6}, {-385E-6, 60E-6}});
	}

	if (diagonal == d45t_56b)
	{
		anal.fc_G = FiducialCut({{-99E-6, 80E-6}, {-100E-6, 36E-6}, {-250E-6, 42E-6}, {-365E-6, 80E-6}, {-265E-6, 130E-6}, {-100E-6, 131E-6}});
	}
}
