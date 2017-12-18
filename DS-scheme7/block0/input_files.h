#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306406;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/406/00000/02C759EF-F6C6-E711-8920-02163E014412.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/406/00000/466246EB-F7C6-E711-AD07-02163E011D0F.root"
	};
}
