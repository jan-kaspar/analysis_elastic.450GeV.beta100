CLASSES_HEADERS=$(shell find classes -name "*.hh")
CLASSES_OBJECTS=$(shell find classes -name "*.cc"|while read f; do echo $${f%.cc}.o; done)

all: \
	classes/AcceptanceCalculator.o \
	classes/Analysis.o \
	classes/command_line_tools.o \
	classes/common_algorithms.o \
	classes/common_alignment.o \
	classes/common_event.o \
	classes/common_init.o \
	classes/Config.o \
	classes/Environment.o \
	classes/FiducialCut.o \
	classes/Kinematics.o \
	classes/numerical_integration.o \
	classes/Stat.o \
	.alignment \
	.alignment_final \
	.alignment_fit \
	.eff3outof4 \
	.eff3outof4_details \
	.eff3outof4_fit \
	.distill \
	.distributions \
	.distributions_anti \
	.pileup \
	.process_timber \
	.resolution_fit \
	.unfolding_cf_mc \
	.unfolding_cf_ni

clean:
	rm -f classes/*.o
	rm -f .alignment \
	rm -f .alignment_final \
	rm -f .alignment_fit \
	rm -f .eff3outof4 \
	rm -f .eff3outof4_details \
	rm -f .eff3outof4_fit \
	rm -f .distill \
	rm -f .distributions \
	rm -f .distributions_anti \
	rm -f .pileup \
	rm -f .process_timber \
	rm -f .resolution_fit \
	rm -f .unfolding_cf_mc \
	rm -f .unfolding_cf_ni

# default classes rule
classes/%.o : classes/%.cc
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) -c $< -o $@

# default program rule
.% : %.cc $(CLASSES_OBJECTS)
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) $(CLASSES_OBJECTS) $< -o $@

# classes dependencies
classes/AcceptanceCalculator.o : classes/Analysis.hh classes/Kinematics.hh classes/numerical_integration.hh

classes/Analysis.o : classes/common_alignment.hh classes/FiducialCut.hh classes/common_event.hh classes/Kinematics.hh classes/common_alignment.hh

classes/command_line_tools.o : 

classes/common_algorithms.o : classes/common_event.hh classes/Environment.hh classes/Analysis.hh classes/Kinematics.hh

classes/common_alignment.o :

classes/common_event.o : classes/common_alignment.hh

classes/common_init.o : classes/Config.hh classes/Environment.hh classes/Analysis.hh

classes/Config.o : 

classes/Environment.o : 

classes/FiducialCut.o : 

classes/Kinematics.o : classes/Environment.hh

classes/numerical_integration.o : 

classes/Stat.o : 