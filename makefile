all: \
	test_program

# default rule
% : %.cc classes/AcceptanceCalculator.hh classes/Analysis.hh classes/command_line_tools.hh classes/common_algorithms.hh\
		classes/common_alignment.hh classes/common_init.hh classes/common_event.hh classes/Config.hh classes/Environment.hh\
		classes/FiducialCut.hh classes/Kinematics.hh classes/numerical_integration.hh
	@ echo "* $@"
	@g++ --std=c++17 `root-config --libs` -lMinuit `root-config --cflags` -O3 -Wall  -Wextra -Wno-attributes -g \
		$(INCS_LIBS) \
		$< -o $@

# extra dependencies
