#include "common_init.hh"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSetReader/interface/ParameterSetReader.h"

//----------------------------------------------------------------------------------------------------

Config cfg;
Environment env;
Analysis anal;

const int rcIncompatibleDiagonal = 123;

//----------------------------------------------------------------------------------------------------

int Init(const string &cfg_file, const string &diagonal_input)
{
	// check diagonal_input
	cfg.diagonal = dUnknown;
	cfg.diagonal_str = diagonal_input;

	if (cfg.diagonal_str == "45b_56t")
	{
		cfg.diagonal = d45b_56t;
		cfg.th_y_sign = +1.;
		cfg.python_object = "cfg_45b_56t";
	}

	if (cfg.diagonal_str == "45t_56b")
	{
		cfg.diagonal = d45t_56b;
		cfg.th_y_sign = -1.;
		cfg.python_object = "cfg_45t_56b";
	}
	
	if (cfg.diagonal_str == "combined")
	{
		cfg.diagonal = dCombined;
		cfg.python_object = "cfg";
	}
	
	if (cfg.diagonal_str == "45b_56b")
	{
		cfg.diagonal = ad45b_56b;
		cfg.th_y_sign = -1.;
		cfg.python_object = "cfg_45b_56b";
	}

	if (cfg.diagonal_str == "45t_56t")
	{
		cfg.diagonal = ad45t_56t;
		cfg.th_y_sign = +1.;
		cfg.python_object = "cfg_45t_56t";
	}

	if (cfg.diagonal == dUnknown)
	{
		printf("ERROR in Init: unrecognised diagonal %s\n", cfg.diagonal_str.c_str());
		return 1;
	}

	// load python config
	edm::ParameterSet config;
	
	try {
		config = edm::readPSetsFrom(cfg_file)->getParameter<edm::ParameterSet>(cfg.python_object);
	}
	catch (...)
	{
		printf("ERROR in Init: cannot load object '%s' from file '%s'.\n", cfg.python_object.c_str(), cfg_file.c_str());
		return 2;
	}

	cfg.Load(config);

	const edm::ParameterSet &ps_env = config.getParameterSet("env");
	env.Load(ps_env);

	const edm::ParameterSet &ps_anal = config.getParameterSet("anal");
	anal.Load(ps_anal);

	return 0;
}

//----------------------------------------------------------------------------------------------------

void PrintConfiguration()
{
	printf("\n");
	printf("-------------------------------- config ---------------------------------\n");
	cfg.Print();
	printf("------------------------------ environment ------------------------------\n");
	env.Print();
	printf("------------------------------- analysis --------------------------------\n");
	anal.Print();
	printf("-------------------------------------------------------------------------\n");
	printf("\n");
}
