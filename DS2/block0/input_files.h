#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 315934;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.0_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.1_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.2_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.3_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.4_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.5_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315934.6_re_reco.root"
	};
}
