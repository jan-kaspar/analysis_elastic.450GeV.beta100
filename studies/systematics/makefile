PROGRAMS=mc_simu mc_process ni_simu ni_process matrix optics_scaling_matrix

all: $(PROGRAMS)

% : %.cc input_distributions.hh scenarios.hh $(BASE_DIR)/classes/*.o
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) $(BASE_DIR)/classes/*.o $< -o $@