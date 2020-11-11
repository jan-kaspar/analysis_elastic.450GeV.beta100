PROGRAMS=single_arm double_arm double_arm_realistic

all: $(PROGRAMS)

clean:
	rm -f $(PROGRAMS)

% : %.cc apertures.hh aperture_list.hh $(BASE_DIR)/classes/*.o
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) $(BASE_DIR)/classes/*.o $< -o $@