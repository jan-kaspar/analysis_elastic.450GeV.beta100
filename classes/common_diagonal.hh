#ifndef _common_diagonal_hh_
#define _common_diagonal_hh_

#include <string>

// TODO: clean
/*
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>

#include "TGraph.h"
#include "TFile.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TMatrixDSymEigen.h"
#include "TRandom2.h"
*/

using namespace std;

//----------------------------------------------------------------------------------------------------

enum DiagonalType { dUnknown, d45b_56t, d45t_56b, dCombined, ad45b_56b, ad45t_56t };

DiagonalType diagonal = dUnknown;

double th_y_sign = 0.;

//----------------------------------------------------------------------------------------------------

int rcIncompatibleDiagonal = 123;

//----------------------------------------------------------------------------------------------------

void Init(const std::string &dgnStr)
{
	// ---------- apply standard settings ----------

	Init_base();

	diagonal = dUnknown;

	if (dgnStr.compare("45b_56t") == 0)
	{
		Init_45b_56t();
		diagonal = d45b_56t;
		th_y_sign = +1.;
	}

	if (dgnStr.compare("45t_56b") == 0)
	{
		Init_45t_56b();
		diagonal = d45t_56b;
		th_y_sign = -1.;
	}
	
	if (dgnStr.compare("combined") == 0)
	{
		diagonal = dCombined;
	}
	
	if (dgnStr.compare("45b_56b") == 0)
	{
		diagonal = ad45b_56b;

		Init_45t_56b();
		th_y_sign = -1.;
	}

	if (dgnStr.compare("45t_56t") == 0)
	{
		diagonal = ad45t_56t;

		Init_45b_56t();
		th_y_sign = +1.;
	}

	if (diagonal == dUnknown)
	{
		printf("Init > unrecognised diagonal %s\n", dgnStr.c_str());
	}

	// ---------- apply additional settings, if any ----------

#ifdef USE_INIT_ADDITIONAL
	printf(">> Applying Init_additional\n");
	Init_additional();
#endif

	// ---------- print important information ----------

	/*
	printf(">> bunchMap\n");
	for (BunchMap::iterator rit = bunchMap.begin(); rit != bunchMap.end(); ++rit)
	{
		printf("\trun %u: ", rit->first);
		for (unsigned int i = 0; i < rit->second.size(); i++)
		{
			if (i > 0)
				printf(", ");
			printf("%u", rit->second[i]);
		}
		printf("\n");
	}
	*/
}

#endif
