#include "parameters_global.h"

unsigned int timestamp_min = 130750;
unsigned int timestamp_max = 143443;

string timberDir = "2018_10_12_fill7284";

void Init_base()
{
	// load global settings
	Init_global();

	anal.alignment_t0 = timestamp_min;
	anal.alignment_ts = (timestamp_max - timestamp_min) / 2.;

	//env.UseMatchedOptics();
}

//----------------------------------------------------------------------------------------------------

void Init_45b_56t()
{
	Init_global_45b_56t();

	// normalisation settings
	anal.L_int = 6.5085E+04;
}

//----------------------------------------------------------------------------------------------------

void Init_45t_56b()
{
	Init_global_45t_56b();

	// normalisation settings
	anal.L_int = 6.7385E+04;
}
