#ifndef _FiducialCut_hh_
#define _FiducialCut_hh_

namespace edm
{
	class ParameterSet;
}

#include <vector>
#include <set>
#include <tuple>

using namespace std;

//----------------------------------------------------------------------------------------------------

struct FiducialCut
{
	struct Point
	{
		double x, y;
	};

	vector<Point> points;

	static constexpr double mi_inf = -10.;
	static constexpr double pl_inf = +10.;

	static constexpr bool debug = false;

	FiducialCut() {}

	FiducialCut(const vector<Point> & _points) : points(_points)
	{
	}

	void Init(const std::vector<edm::ParameterSet> &input);

	void Print() const;

	void Shift(double x, double y);

	void ApplyCDTransform(double C, double D);

	void Scale(double x, double y);

	bool Satisfied(double th_x, double th_y) const;

	// returns th_y_min, th_y_max
	std::tuple<double, double> GetThYRange(double th_x) const;

	vector<Point> GetIntersectionPhis(double th) const;
};

#endif
