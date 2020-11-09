all: merge

% : %.cc
	@echo "BUILDING $@"
	@g++ $(GCC_OPT) $(INCS_LIBS) ../classes/command_line_tools.o $< -o $@
