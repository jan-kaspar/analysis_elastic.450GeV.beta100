#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 323932;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.0_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.1_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.2_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.3_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.4_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.5_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.6_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.7_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.8_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323932.9_reco_ZeroBias.root"
	};
}
