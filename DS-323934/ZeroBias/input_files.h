#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 323934;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.0_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.1_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.2_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.3_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.4_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.5_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.6_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.7_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.8_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323934.9_reco_ZeroBias.root"
	};
}
