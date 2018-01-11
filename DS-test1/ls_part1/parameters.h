#include "../parameters.h"

#define USE_INIT_ADDITIONAL 1

void Init_additional()
{
	for (auto &f : distilledNtuples)
		f = "../" + f;

	anal.lumi_section_min = 2;
	anal.lumi_section_max = 39;
}
