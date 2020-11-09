all: \
	compare	

# default rule
% : %.cc 
	@ echo "BUILDING $@"
	@g++ --std=c++17 `root-config --libs` -lMinuit `root-config --cflags` -O3 -Wall  -Wextra -Wno-attributes -g \
		$(INCS_LIBS) \
		$< -o $@
