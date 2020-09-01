#include "parameters_global.h"

double timestamp_min = 1.5E3, timestamp_max = 32.0E3;

void Init_base()
{
	// load global settings
	Init_global();
}

//----------------------------------------------------------------------------------------------------

void Init_45b_56t()
{
	Init_global_45b_56t();
}

//----------------------------------------------------------------------------------------------------

void Init_45t_56b()
{
	Init_global_45t_56b();
}
