#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 323893;

	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.0_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.1_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.2_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.3_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.4_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.5_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.6_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.7_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.8_reco_ZeroBias.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/test_2018_10_02//version1_ZeroBias/run_323893.9_reco_ZeroBias.root"
	};
}
