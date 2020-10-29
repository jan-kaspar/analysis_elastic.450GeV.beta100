#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

std::vector<std::string> input_files;

void InitInputFiles()
{
	input_files = {
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324467.0_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324469.0_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324469.1_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324471.0_re_reco_Totem1.root",
		"root://eostotem.cern.ch///eos/totem/data/offline/2018/450GeV/beta100/Totem1/version4/run_324471.1_re_reco_Totem1.root"
	};
}
