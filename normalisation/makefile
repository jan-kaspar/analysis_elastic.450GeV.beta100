all: \
	normalisation_ref \

normalisation_ref: normalisation_ref.cc
	g++ `root-config --libs` -lMinuit `root-config --cflags` -O3 -Wall -g \
		normalisation_ref.cc -o normalisation_ref
