#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 306989;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2017H/Totem12/MINIAOD/PromptReco-v1/000/306/989/00000/1817003D-42D1-E711-BA34-02163E019E3D.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2017H/Totem12/MINIAOD/PromptReco-v1/000/306/989/00000/FE51FC35-4AD1-E711-A007-02163E013737.root"
	};
}
