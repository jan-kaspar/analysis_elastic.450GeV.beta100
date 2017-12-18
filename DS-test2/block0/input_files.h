#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306984;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017H/Totem12/MINIAOD/PromptReco-v1/000/306/984/00000/C2F5545C-3BD1-E711-9D7E-02163E019D30.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017H/Totem12/MINIAOD/PromptReco-v1/000/306/984/00000/D22A10E2-37D1-E711-B4A2-02163E01410E.root"
	};
}
