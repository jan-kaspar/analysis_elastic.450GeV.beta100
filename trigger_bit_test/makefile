all: test

test : test.cc
	g++ -O3 -Wall -Wextra -Wno-attributes --std=c++11\
			`root-config --libs` -lMinuit -lMinuit2 `root-config --cflags` \
			-I"$(CMSSW_BASE)/src" \
			-I"$(CMSSW_RELEASE_BASE)/src" \
			-L"$(CMSSW_BASE)/lib/slc6_amd64_gcc630" \
			-L"$(CMSSW_RELEASE_BASE)/lib/slc6_amd64_gcc630" \
			-lDataFormatsFWLite \
			-lDataFormatsCommon \
			-lDataFormatsCTPPSDetId \
			-lDataFormatsProvenance \
		test.cc -o test
