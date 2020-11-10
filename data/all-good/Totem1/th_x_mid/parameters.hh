#define USE_INIT_ADDITIONAL

#include "../../parameters.hh"

void Init_additional()
{
	if (diagonal == d45b_56t)
	{
		//anal.fc_L = FiducialCut({{-96E-6, 80E-6}, {-95E-6, 34E-6}, {+95E-6, 38E-6}, {+96E-6, 80E-6}, {+95E-6, 123E-6}, {-95E-6, 125E-6}});
		//anal.fc_R = FiducialCut({{-96E-6, 80E-6}, {-95E-6, 34E-6}, {+95E-6, 38E-6}, {+96E-6, 80E-6}, {+95E-6, 123E-6}, {-95E-6, 125E-6}});
		anal.fc_G = FiducialCut({{-101E-6, 80E-6}, {-100E-6, 32E-6}, {+100E-6, 36E-6}, {+101E-6, 80E-6}, {+100E-6, 125E-6}, {-100E-6, 127E-6}});
	}

	if (diagonal == d45t_56b)
	{
		//anal.fc_L = FiducialCut({{-52E-6, 30E-6}, {-105E-6, 34E-6}, {-106E-6, 80E-6}, {-105E-6, 133E-6}, {+105E-6, 133E-6}, {+106E-6, 80E-6}, {+105E-6, 30E-6}});
		//anal.fc_R = FiducialCut({{-52E-6, 30E-6}, {-105E-6, 34E-6}, {-106E-6, 80E-6}, {-105E-6, 133E-6}, {+105E-6, 133E-6}, {+106E-6, 80E-6}, {+105E-6, 30E-6}});
		anal.fc_G = FiducialCut({{-50E-6, 32E-6}, {-100E-6, 36E-6}, {-101E-6, 80E-6}, {-100E-6, 131E-6}, {+100E-6, 131E-6}, {+101E-6, 80E-6}, {+100E-6, 32E-6}});
	}
}
