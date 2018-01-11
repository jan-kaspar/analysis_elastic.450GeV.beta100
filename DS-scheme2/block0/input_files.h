#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306379;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/379/00000/1A5325CB-F1C6-E711-92E4-02163E011B4F.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/379/00000/6C92E45C-00C7-E711-956E-02163E01361C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/379/00000/9030C216-01C7-E711-A723-02163E012130.root"
	};
}
