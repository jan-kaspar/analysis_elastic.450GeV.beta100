#include "parameters_global.hh"

unsigned int timestamp_min = 78681;
unsigned int timestamp_max = 244931;

string timberDir = "no_timber_dir";

void Init_base()
{
	// load global settings
	Init_global();

	// select input
	distilledNtuples.clear();
	distilledNtuples.push_back("../../../DS-fill7280/Totem1");
	distilledNtuples.push_back("../../../DS-fill7281/Totem1");
	distilledNtuples.push_back("../../../DS-fill7282/Totem1");
	distilledNtuples.push_back("../../../DS-fill7283/Totem1");
	distilledNtuples.push_back("../../../DS-fill7284/Totem1");
	distilledNtuples.push_back("../../../DS-fill7285/Totem1");
	distilledNtuples.push_back("../../../DS-fill7289/Totem1");
	distilledNtuples.push_back("../../../DS-fill7291/Totem1");

	// update settings
	anal.alignment_t0 = timestamp_min;
	anal.alignment_ts = (timestamp_max - timestamp_min) / 2.;

	//env.UseMatchedOptics();
}

//----------------------------------------------------------------------------------------------------

void Init_45b_56t()
{
	Init_global_45b_56t();

	// TODO: update
	// normalisation settings
	anal.L_int = 6.4186E+04;
}

//----------------------------------------------------------------------------------------------------

void Init_45t_56b()
{
	Init_global_45t_56b();

	// TODO: update
	// normalisation settings
	anal.L_int = 6.6562E+04;
}
