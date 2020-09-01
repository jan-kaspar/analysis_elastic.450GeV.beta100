#define USE_INIT_ADDITIONAL

#include "../../parameters.h"

void Init_additional()
{
	if (diagonal == d45b_56t)
	{
		//anal.fc_L = FiducialCut({{+104E-6, 80E-6}, {+105E-6, 38E-6}, {250E-6, 44E-6}, {380E-6, 80E-6}, {265E-6, 122E-6}, {+105E-6, 123E-6}});
		//anal.fc_R = FiducialCut({{+104E-6, 80E-6}, {+105E-6, 38E-6}, {250E-6, 44E-6}, {380E-6, 80E-6}, {265E-6, 122E-6}, {+105E-6, 123E-6}});
		anal.fc_G = FiducialCut({{+99E-6, 80E-6}, {+100E-6, 36E-6}, {250E-6, 42E-6}, {385E-6, 80E-6}, {270E-6, 124E-6}, {+100E-6, 125E-6}});
	}

	if (diagonal == d45t_56b)
	{
		anal.fc_G = FiducialCut({{99E-6, 80E-6}, {+100E-6, 131E-6}, {250E-6, 132E-6}, {355E-6, 95E-6}, {375E-6, 43E-6}, {330E-6, 32E-6}, {+100E-6, 32E-6}});
	}
}
