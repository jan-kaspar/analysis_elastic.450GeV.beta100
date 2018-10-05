#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 323919;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323919.6_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323919.7_reco_ZeroBias.root"
	};
}
