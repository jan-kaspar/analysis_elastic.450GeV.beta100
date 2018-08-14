#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

unsigned int run;

std::vector<std::string> input_files;

void InitInputFiles()
{
	run = 315956;

	input_files = {
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/100000/5C54ED61-2B6D-E811-82D6-FA163EF75B2B.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/100000/EA66D91C-2F6D-E811-9FD2-842B2B42B2AF.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/100000/3CA1E305-AB6C-E811-8FC7-0CC47A13CD44.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias1/AOD/06Jun2018-v1/100000/76280326-CC6D-E811-B40E-24BE05CEEB81.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/50000/F22424E8-326A-E811-8047-001A649D4B01.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias2/AOD/06Jun2018-v1/50000/A65C6BFB-326A-E811-B69A-F01FAFE5D4D6.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/30000/98243333-6F6F-E811-93E0-008CFA1660A8.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/30000/BE6E4BAA-6F6F-E811-A0CE-002590791D60.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/30000/DEE7791F-6F6F-E811-B014-1866DA85D9A7.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/30000/96875AA4-706F-E811-AFD3-0CC47A4D76A0.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias3/AOD/06Jun2018-v1/30000/48C393ED-6E6F-E811-A909-C81F66B78748.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/34B389A2-4D6E-E811-A884-F01FAFE29BBE.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/14BE29D7-336E-E811-BD77-001E67A40523.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/A62F5271-406E-E811-B1D9-0025907D2430.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias4/AOD/06Jun2018-v1/30000/C2125124-8A6E-E811-A794-0CC47A6C0716.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/10BEC44E-346E-E811-856B-1418774A2960.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/2611E206-C46D-E811-845B-00000086FE80.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/1C8A76E3-1B6D-E811-B54A-FA163E2B576B.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias5/AOD/06Jun2018-v1/100000/E03A0619-EB6D-E811-9305-1866DAEA8230.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/64DAFBB9-D86B-E811-8890-0CC47AA4861C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias6/AOD/06Jun2018-v1/80000/D8BFE442-D66B-E811-9341-FA163ED667D8.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/60000/56CF2458-4B6E-E811-87E6-008CFA197900.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/60000/484B988D-4D6E-E811-A4AA-00266CFFC9C4.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/60000/60A9385C-846B-E811-953E-7CD30AB0522C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias7/AOD/06Jun2018-v1/60000/46F88C86-4B6E-E811-8485-4C79BA320CED.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/ECE4805A-4F6A-E811-8EB5-008CFA110C8C.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/8C211855-4F6A-E811-96AA-4C79BA1813B1.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/883D1F68-4F6A-E811-8EB3-00238BCE463E.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias8/AOD/06Jun2018-v1/60000/12858457-426A-E811-8AA9-B4E10FD21863.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/E8DC1295-AE6D-E811-9609-0025904AC2C4.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias9/AOD/06Jun2018-v1/100000/EA200452-F76C-E811-8CAF-FA163E65CD15.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/3C46D4F2-FE6D-E811-AB7F-002590E3A222.root",
		"root://cmsxrootd.fnal.gov///store/data/Run2018A/ZeroBias10/AOD/06Jun2018-v1/30000/62CFE74D-C76E-E811-8C60-0CC47A6C14C8.root"
	};
}
