INCS = -I$(GSL_DIR)/include
LIBS = -L$(GSL_DIR)/lib -lgsl -lgslcblas -lm

all: single_arm double_arm double_arm_realistic

single_arm: single_arm.cc ../common_definitions.h ../common_parameters.h apertures.h aperture_list.h
	g++ --std=c++11 `root-config --libs` -lMinuit `root-config --cflags` -O3 -g -Wall -Wextra \
		single_arm.cc -o single_arm

double_arm: double_arm.cc ../common_definitions.h ../common_parameters.h apertures.h aperture_list.h
	g++ --std=c++11 `root-config --libs` -lMinuit `root-config --cflags` -O3 -g -Wall -Wextra \
		double_arm.cc -o double_arm

double_arm_realistic: double_arm_realistic.cc ../common_definitions.h ../common_parameters.h ../AcceptanceCalculator.h apertures.h aperture_list.h parameters_test.h
	g++ --std=c++11 `root-config --libs` -lMinuit `root-config --cflags` -O3 -g -Wall -Wextra \
		-I ../ $(INCS) $(LIBS) \
		double_arm_realistic.cc -o double_arm_realistic
