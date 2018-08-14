#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 315934;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/60000/04480083-4B6E-E811-9678-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/60000/5A9E4235-4B6E-E811-A78D-FA163EE1837C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/4626AB23-576A-E811-AA44-003048F2E726.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/E6EE7993-D26A-E811-ACC1-C81F66B78FF4.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/661D6987-D26A-E811-BAE0-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/4E458DCA-D36A-E811-92E4-001A649D500D.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/0AFE1515-8F6C-E811-B303-4C79BA180B3F.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/F8B9DAFB-4C6D-E811-BB66-1866DA85DCAB.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/FCBEC7A5-706D-E811-8128-FA163E2B26F7.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/8CF5E082-236C-E811-ABD2-FA163E36E1E5.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/901DABE3-1A6E-E811-9533-008CFA197904.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/9C982EEB-956D-E811-ADAA-44A8420CC3DC.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/A62F5271-406E-E811-B1D9-0025907D2430.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/8AE6844E-B96D-E811-94EF-0CC47AD98C8C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/A08EB339-BE6D-E811-817B-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/30A08714-D36C-E811-BC5F-E0071B7B2320.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/10BEC44E-346E-E811-856B-1418774A2960.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/1C8A76E3-1B6D-E811-B54A-FA163E2B576B.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/6A750F86-946B-E811-AE4C-8CDCD4A9A484.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/7073F577-866B-E811-A9FC-D48564456546.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/6670E39C-B26B-E811-84C0-002590DB9270.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/7074F0CB-776B-E811-A135-3417EBE70069.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/D8BFE442-D66B-E811-9341-FA163ED667D8.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/710000/0CBC64F3-456E-E811-A8D0-3417EBE7062D.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/086950A1-A06C-E811-BC95-1866DA85DFC0.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/20B844EA-0A6D-E811-8652-E0071B7A8570.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/5299C843-C96D-E811-B934-5065F3810301.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/A80951CB-256D-E811-BBC3-FA163E3FD20C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/9CB63F00-376A-E811-A4DE-0CC47AB6503C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/06FCC2A3-426A-E811-88DB-44A8420CBDE2.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/E27CF755-4F6A-E811-BA55-1866DAEB296C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/8C211855-4F6A-E811-96AA-4C79BA1813B1.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/883D1F68-4F6A-E811-8EB3-00238BCE463E.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/12858457-426A-E811-8AA9-B4E10FD21863.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/A443D250-F36C-E811-9319-24BE05C3B8B1.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/6E1863CB-286F-E811-9F57-0CC47A4C8F12.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/2C7E85B7-0C6D-E811-8858-FA163EE2E135.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/CC6E9929-B96D-E811-89CE-24BE05C68681.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/3C46D4F2-FE6D-E811-AB7F-002590E3A222.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/588CF5BB-7A6E-E811-AE2D-008CFA165F34.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/38132DF1-746E-E811-82A1-A4BF0126D535.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/D855B069-6E6E-E811-8499-002590D9D89C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/92173B25-936E-E811-82CE-1866DA7F95AE.root"
	};
}
