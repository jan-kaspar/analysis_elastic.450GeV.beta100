#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306402;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/402/00000/44F5D86A-FFC6-E711-916A-02163E01A6EE.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/402/00000/C4CBE038-F6C6-E711-8F61-02163E011DEE.root"
	};
}
