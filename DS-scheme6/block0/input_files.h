#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306405;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/405/00000/E2C0DF25-F7C6-E711-9EE5-02163E01A40D.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/405/00000/FEEA3363-06C7-E711-BA42-02163E01390C.root"
	};
}
