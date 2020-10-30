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

	void Load(const edm::ParameterSet &ps);

	void Print() const;
};

//----------------------------------------------------------------------------------------------------

void Config::Load(const edm::ParameterSet & /*ps*/)
{
}

//----------------------------------------------------------------------------------------------------

void Config::Print() const
{
}

#endif