#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 315956;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.0_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.1_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.2_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.3_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.4_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.5_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.6_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.7_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.8_re_reco.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_05_08/version1/run_315956.9_re_reco.root"
	};
}
