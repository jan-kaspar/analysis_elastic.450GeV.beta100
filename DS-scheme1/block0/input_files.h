#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306373;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/373/00000/0CA81F29-FDC6-E711-829B-02163E019E5D.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/373/00000/16D9DD29-21C7-E711-9AC6-02163E012B76.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/373/00000/302CAAB8-F4C6-E711-9CEA-02163E019BB3.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/373/00000/34F49DE1-0BC7-E711-A606-02163E019C46.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/373/00000/70C753C7-F7C6-E711-AAE0-02163E013942.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017F/ZeroBias/AOD/PromptReco-v1/000/306/373/00000/F8F917A3-01C7-E711-B981-02163E011FA9.root"
	};
}
