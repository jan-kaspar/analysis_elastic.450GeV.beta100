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

	// +1 for 45b_56t, -1 for 45t_56b
	double th_y_sign = 0.;

	// list of input EDM files
	vector<string> input_files;

	// list of distilled file directories
	vector<string> distilled_files;

	// global offset between UNIX time and timestamps used in the analysis
	double timestamp0;

	// range of timestamps (UNIX time - timestamp0)
	double timestamp_min, timestamp_max;

	void Load(const edm::ParameterSet &ps);

	void Print() const;
};

//----------------------------------------------------------------------------------------------------

void Config::Load(const edm::ParameterSet & ps)
{
	input_files = ps.getParameter<vector<string>>("input_files");
	distilled_files = ps.getParameter<vector<string>>("distilled_files");

	timestamp0 = ps.getParameter<double>("timestamp0");

	timestamp_min = ps.getParameter<double>("timestamp_min");
	timestamp_max = ps.getParameter<double>("timestamp_max");
}

//----------------------------------------------------------------------------------------------------

void Config::Print() const
{
	printf("%lu input_files:\n", input_files.size());
	for (const auto &f : input_files)
		printf("  %s\n", f.c_str());

	printf("%lu distilled_files:\n", distilled_files.size());
	for (const auto &f : distilled_files)
		printf("  %s\n", f.c_str());

	printf("timestamp0 = %.1f\n", timestamp0);
	printf("timestamp_min = %.1f\n", timestamp_min);
	printf("timestamp_max = %.1f\n", timestamp_max);
}

#endif