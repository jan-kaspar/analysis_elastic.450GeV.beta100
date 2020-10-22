#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

std::vector<std::string> input_files;

void InitInputFiles()
{
	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324498.0_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324498.1_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324509.0_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324509.1_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324513.0_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324513.1_re_reco_Totem1.root"
	};
}
