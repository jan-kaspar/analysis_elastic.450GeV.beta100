#ifndef _common_init_hh_
#define _common_init_hh_

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSetReader/interface/ParameterSetReader.h"

#include "Config.hh"
#include "Environment.hh"
#include "Analysis.hh"

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
		printf("ERROR: in Init > unrecognised diagonal %s\n", cfg.diagonal_str.c_str());
		return 1;
	}

	// load python config
	const edm::ParameterSet &config = edm::readPSetsFrom(cfg_file)->getParameter<edm::ParameterSet>(cfg.python_object);

	cfg.Load(config);

	const edm::ParameterSet &ps_env = config.getParameterSet("env");
	env.Load(ps_env);

	const edm::ParameterSet &ps_anal = config.getParameterSet("anal");
	anal.Load(ps_anal);

	return 0;
}

#endif
