#ifndef _config_hh_
#define _config_hh_

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSetReader/interface/ParameterSetReader.h"

#include "Environment.hh"
#include "Analysis.hh"

#include <vector>
#include <string>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct Config
{
	string diagonal;

	double L_int;

	void Load(const edm::ParameterSet &ps);

	void Print() const;
};

//----------------------------------------------------------------------------------------------------

void Config::Load(const edm::ParameterSet &ps)
{
	L_int = ps.getParameter<double>("L_int");
}

//----------------------------------------------------------------------------------------------------

void Config::Print() const
{
	printf("L_int = %.3f\n", L_int);
}

//----------------------------------------------------------------------------------------------------

Config cfg;
Environment env;
Analysis anal;

//----------------------------------------------------------------------------------------------------

int LoadConfig(const string &file, const string &obj)
{
	const edm::ParameterSet &config = edm::readPSetsFrom(file)->getParameter<edm::ParameterSet>(obj);

	// TODO: uncomment
	/*
	const edm::ParameterSet &ps_env = config.getParameterSet("env");
	env.Load(ps_env);

	// TODO: uncomment
	//const edm::ParameterSet &ps_anal = config.getParameterSet("anal");
	//anal.Load(ps_anal);
	*/

	return 0;
}

#endif