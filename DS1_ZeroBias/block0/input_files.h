#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 315922;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/60000/D6C4EFE0-BB6B-E811-A596-782BCB38F205.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/60000/6EDD385F-4B6E-E811-8BFF-008CFA165F44.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/60000/04480083-4B6E-E811-9678-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/60000/5A9E4235-4B6E-E811-A78D-FA163EE1837C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/4626AB23-576A-E811-AA44-003048F2E726.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/E6EE7993-D26A-E811-ACC1-C81F66B78FF4.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/30000/661D6987-D26A-E811-BAE0-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/6420F104-396C-E811-A9CE-1866DA85D9BF.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/3A91872D-C56B-E811-A1B2-5065F381C251.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/0AFE1515-8F6C-E811-B303-4C79BA180B3F.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/F8B9DAFB-4C6D-E811-BB66-1866DA85DCAB.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/FCBEC7A5-706D-E811-8128-FA163E2B26F7.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/80000/E8347161-B570-E811-87B2-0025905A60F2.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/0456C774-2A6E-E811-A086-549F3525C0BC.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/901DABE3-1A6E-E811-9533-008CFA197904.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/9C982EEB-956D-E811-ADAA-44A8420CC3DC.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/7E82ABEF-296E-E811-AAAD-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/34B389A2-4D6E-E811-A884-F01FAFE29BBE.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/B6784C77-6F6D-E811-B17B-1418774A25AB.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/14BE29D7-336E-E811-BD77-001E67A40523.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/A62F5271-406E-E811-B1D9-0025907D2430.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/8AE6844E-B96D-E811-94EF-0CC47AD98C8C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/A08EB339-BE6D-E811-817B-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/30A08714-D36C-E811-BC5F-E0071B7B2320.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/10BEC44E-346E-E811-856B-1418774A2960.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/1C8A76E3-1B6D-E811-B54A-FA163E2B576B.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/C4556E39-BE6D-E811-8903-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/7073F577-866B-E811-A9FC-D48564456546.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/7074F0CB-776B-E811-A135-3417EBE70069.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/D8BFE442-D66B-E811-9341-FA163ED667D8.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/C89ACD7A-866B-E811-B673-441EA158FE40.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/710000/0CBC64F3-456E-E811-A8D0-3417EBE7062D.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/DACDBA36-EB6D-E811-B364-1866DAEA7C48.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/086950A1-A06C-E811-BC95-1866DA85DFC0.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/DE1AB441-E26C-E811-9B34-801844E56C20.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/72135C92-F36C-E811-AABA-008CFAF72A64.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/5CF22AAA-F36C-E811-9CEE-0CC47A0AD668.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/20B844EA-0A6D-E811-8652-E0071B7A8570.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/5299C843-C96D-E811-B934-5065F3810301.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/540D4F93-EC6C-E811-9718-002590E3A004.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/6E09435F-B26C-E811-9687-A4BF011257C0.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/E238AD89-E36C-E811-B97C-0025905C5484.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/100000/A80951CB-256D-E811-BBC3-FA163E3FD20C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/3A300BA4-5A6A-E811-A4C9-0025905D1D52.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/9CB63F00-376A-E811-A4DE-0CC47AB6503C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/06FCC2A3-426A-E811-88DB-44A8420CBDE2.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/8C211855-4F6A-E811-96AA-4C79BA1813B1.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/883D1F68-4F6A-E811-8EB3-00238BCE463E.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/12858457-426A-E811-8AA9-B4E10FD21863.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/243602DA-2E6A-E811-8F43-0CC47A544F5A.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/E8DC1295-AE6D-E811-9609-0025904AC2C4.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/A443D250-F36C-E811-9319-24BE05C3B8B1.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/6E1863CB-286F-E811-9F57-0CC47A4C8F12.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/2EB9C394-CD6C-E811-B462-0CC47AD98D0C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/FEE5A5B3-CF6C-E811-A677-B083FED42487.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/6E1EEDEE-EF6C-E811-95CB-A4BF0100DD3E.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/208C6BD5-CF6C-E811-A16C-F01FAFE15857.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/40B53903-036D-E811-9EA2-008CFA110C5C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/2C7E85B7-0C6D-E811-8858-FA163EE2E135.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/CC6E9929-B96D-E811-89CE-24BE05C68681.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/E4659057-4D6E-E811-B603-F01FAFD9C974.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/603DED58-6E6E-E811-BD75-141877410340.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/3C46D4F2-FE6D-E811-AB7F-002590E3A222.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/588CF5BB-7A6E-E811-AE2D-008CFA165F34.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/38132DF1-746E-E811-82A1-A4BF0126D535.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/D855B069-6E6E-E811-8499-002590D9D89C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/92173B25-936E-E811-82CE-1866DA7F95AE.root"
	};
}
