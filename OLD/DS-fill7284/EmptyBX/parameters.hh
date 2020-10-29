#include "parameters_global.hh"

unsigned int timestamp_min = 206071;
unsigned int timestamp_max = 218141;

void Init_base()
{
	// load global settings
	Init_global();

	keepAllBunches = false;
	bunchMap[324485] = { 462, 520 };

	//env.UseMatchedOptics();
}

//----------------------------------------------------------------------------------------------------

void Init_45b_56t()
{
	Init_global_45b_56t();

	// normalisation settings
	anal.L_int = 1.;
}

//----------------------------------------------------------------------------------------------------

void Init_45t_56b()
{
	Init_global_45t_56b();

	// normalisation settings
	anal.L_int = 1.;
}
