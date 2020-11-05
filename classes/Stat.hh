#ifndef _Stat_hh_
#define _Stat_hh_

#include "TMatrixDSym.h"

#include <vector>
#include <string>
#include <cmath>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct Stat
{
	unsigned int dim;
	double S1;
	vector<double> Sv, Svv, Svvv, Svvvv;

	vector< vector<double> > Sxy, Sxxy, Sxyy, Sxxyy;

	vector<string> labels;

	void Init(unsigned int _dim = 1);

	Stat() {}

	Stat(unsigned int _dim)
	{
		Init(_dim);
	}

	void SetLabels(const vector<string> &_l);

	template <class T>
	void Fill(const T &v);

	void Fill(double v1, double v2 = 0., double v3 = 0., double v4 = 0., double v5 = 0.);

	string QLabel(unsigned int i) const;
	
	//--------------------
	// 1D getters
	//--------------------

	double GetEntries() const;

	double GetMean(unsigned int i) const;

	double GetStdDev(unsigned int i) const;

	double GetMeanUnc(unsigned int i) const;

	double GetStdDevUnc(unsigned int i) const;

	// approximation of GetStdDevUnc valid for Gaussian distributions
	double GetStdDevUncGauss(unsigned int i) const;
	
	//--------------------
	// 2D getters
	//--------------------

	double GetCovariance(unsigned int i, unsigned int j) const;

	double GetCorrelation(unsigned int i, unsigned int j) const;

	double GetCovarianceUnc(unsigned int i, unsigned int j) const;

	double GetCorrelationUnc(unsigned int i, unsigned int j) const;

	TMatrixDSym GetCovarianceMatrix() const;

	//--------------------
	// print methods
	//--------------------

	void PrintStat() const;

	void PrintMeanAndStdDev() const;
	
	void PrintCovariance() const;

	void PrintCorrelation() const;
};

#endif
