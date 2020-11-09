all: merge

% : %.cc
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) $(CLASSES_OBJECTS) $< -o $@
