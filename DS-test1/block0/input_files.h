#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306982;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017H/Totem12/MINIAOD/PromptReco-v1/000/306/982/00000/5A5E0BB0-2BD1-E711-80BC-02163E012055.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017H/Totem12/MINIAOD/PromptReco-v1/000/306/982/00000/5E25CA9C-32D1-E711-9933-02163E0133E0.root"
	};
}
