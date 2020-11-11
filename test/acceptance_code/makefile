PROGRAMS=algorithm_test validation_gaussian_approx mc_resolution_details validation_with_mc

all: $(PROGRAMS)

% : %.cc $(BASE_DIR)/classes/*.o
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) $(BASE_DIR)/classes/*.o $< -o $@