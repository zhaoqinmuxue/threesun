#include "stdafx.h"
#include "vec.h"
#include <cmath>

	Vec::Vec() :x(0), y(0), z(0), mag(0) {}
	Vec::Vec(double n1, double n2, double n3) : x(n1), y(n2), z(n3) { setmag(); }
	Vec::Vec(const Vec& T) : x(T.x), y(T.y), z(T.z), mag(T.mag) {}
	Vec::~Vec() {}

	void Vec::setmag()
	{
		mag = sqrt(x*x + y*y + z*z);
	}

	Vec Vec::operator+(const Vec& T)const
	{
		Vec sum;
		sum.x = x + T.x;
		sum.y = y + T.y;
		sum.z = z + T.z;
		sum.setmag();
		return sum;
	}

	Vec Vec::operator-(const Vec& T)const
	{
		Vec sum;
		sum.x = x - T.x;
		sum.y = y - T.y;
		sum.z = z - T.z;
		sum.setmag();
		return sum;
	}

	Vec Vec::operator/(const double n)const
	{
		Vec sum;
		sum.x = x / n;
		sum.y = y / n;
		sum.z = z / n;
		sum.mag = mag / n;
		return sum;
	}

	Vec Vec::contrary()const
	{
		return Vec(-x, -y, -z);
	}
	std::ostream& operator<<(std::ostream & os, const Vec & T)
	{
		os << T.x << " " << T.y << " " << T.z;
		return os;
	}
