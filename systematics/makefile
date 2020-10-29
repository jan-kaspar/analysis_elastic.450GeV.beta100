all: \
	mc_simu \
	mc_process \
	ni_simu \
	ni_process \
	matrix \
	optics_scaling_matrix

% : %.cc
	g++ --std=c++11 `root-config --libs` -lMinuit `root-config --cflags` -O3 -Wall -g \
		-I.. \
		-I$(GSL_DIR)/include -L$(GSL_DIR)/lib -lgsl -lgslcblas -lm \
		$< -o $@

mc_simu : scenarios.hh input_distributions.hh ../command_line_tools.hh \
		../common_definitions.h ../common_algorithms.h ../AcceptanceCalculator.h \
		parameters.hh ../common.h ../parameters_global.h

ni_simu : scenarios.hh input_distributions.hh ../command_line_tools.hh \
		../common_definitions.h ../common_algorithms.h ../AcceptanceCalculator.h \
		parameters.hh ../common.h ../parameters_global.h

matrix : ../command_line_tools.hh
