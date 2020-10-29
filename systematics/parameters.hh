#include "../parameters_global.hh"

/**
 * IMPORTANT: keep synchronised with parameters.h in the analysis.
 **/

void Init_base()
{
	// load global settings
	Init_global();

	env.UseMatchedOptics();

	// list of (sub-)directories with distilled ntuples
	distilledNtuples.push_back(".");
}

//----------------------------------------------------------------------------------------------------

void Init_45b_56t()
{
	Init_global_45b_56t();

	// TODO: anything needed here?
}

//----------------------------------------------------------------------------------------------------

void Init_45t_56b()
{
	Init_global_45t_56b();

	// TODO: anything needed here?
}
