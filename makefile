all: \
	test_program

# default rule
% : %.cc classes/AcceptanceCalculator.hh classes/Analysis.hh classes/command_line_tools.hh classes/common_algorithms.hh\
		classes/common_alignment.hh classes/common_diagonal.hh classes/common_event.hh classes/Config.hh classes/Environment.hh\
		classes/FiducialCut.hh classes/Kinematics.hh classes/numerical_integration.hh
	g++ --std=c++17 `root-config --libs` -lMinuit `root-config --cflags` -O3 -Wall  -Wextra -Wno-attributes -g \
		-I$(GSL_DIR)/include \
		-L$(GSL_DIR)/lib -lgsl -lgslcblas -lm \
		-I$(CMSSW_BASE)/src \
		-I$(CMSSW_RELEASE_BASE)/src \
		-L$(CMSSW_BASE)/lib/slc7_amd64_gcc820 \
		-L$(CMSSW_RELEASE_BASE)/lib/slc7_amd64_gcc820 \
		-lDataFormatsFWLite -lDataFormatsCommon -lDataFormatsCTPPSDetId -lDataFormatsCTPPSReco -lFWCoreParameterSet -lFWCoreParameterSetReader\
		$< -o $@

# extra dependencies
