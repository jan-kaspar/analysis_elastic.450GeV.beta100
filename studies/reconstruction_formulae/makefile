PROGRAMS=test_formulae_graph test_formulae_correlation print_optics_uncertainties

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

% : %.cc common.hh formulae.hh $(BASE_DIR)/classes/*.o
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) $(BASE_DIR)/classes/*.o $< -o $@