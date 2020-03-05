all: make_fit

make_fit: make_fit.cc
	g++ `root-config --libs` -lMinuit `root-config --cflags` -O3 -Wall -Wextra make_fit.cc -o make_fit
