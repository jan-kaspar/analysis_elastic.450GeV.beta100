#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 323933;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.0_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.13_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.14_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.16_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.19_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.3_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.4_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.6_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323933.8_reco_ZeroBias.root"
	};
}
