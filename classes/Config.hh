#ifndef _config_hh_
#define _config_hh_

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include <vector>
#include <string>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------------------------------------

enum DiagonalType { dUnknown, d45b_56t, d45t_56b, dCombined, ad45b_56b, ad45t_56t };

//----------------------------------------------------------------------------------------------------

struct Config
{
	DiagonalType diagonal = dUnknown;
	string diagonal_str;
	string python_object;

	double th_y_sign = 0.;

	vector<string> input_files;

	double timestamp0;

	void Load(const edm::ParameterSet &ps);

	void Print() const;
};

//----------------------------------------------------------------------------------------------------

void Config::Load(const edm::ParameterSet & ps)
{
	input_files = ps.getParameter<vector<string>>("input_files");

	timestamp0 = ps.getParameter<double>("timestamp0");
}

//----------------------------------------------------------------------------------------------------

void Config::Print() const
{
	printf("%lu input_files:\n", input_files.size());
	for (const auto &f : input_files)
		printf("  %s\n", f.c_str());

	printf("timestamp0 = %.1f\n", timestamp0);	
}

#endif