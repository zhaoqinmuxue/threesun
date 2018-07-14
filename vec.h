#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

#include "stdafx.h"
#include <iostream>
#include <cmath>
#define step 1			//每次计算位置的时间间隔，取了确定的1秒

	class Vec
	{
	private:
		double x;			//矢量的三个分量
		double y;
		double z;
		double mag;		//模长
		void setmag();
	public:
		Vec();													//三种构造函数的重载
		Vec(double n1, double n2, double n3);
		Vec(const Vec& T);
		~Vec();
		double xval()const { return x; }				//用来获取私有成员的值
		double yval()const { return y; }
		double zval()const { return z; }
		double magval()const { return mag; }
		Vec operator+(const Vec& T)const;		//运算符重载，用起来会简洁一些
		Vec operator-(const Vec& T)const;
		template <typename T> Vec operator*(T n)const;
		Vec operator/(const double n)const;
		Vec contrary()const;								//对矢量取相反方向，因为受力是相互的，直接取反可以少算一次
		friend std::ostream& operator<<(std::ostream & os, const Vec & T);
	};

	template <typename T> Vec Vec::operator*(T n)const
	{
		Vec sum;
		sum.x = n*x;
		sum.y = n*y;
		sum.z = n*z;
		sum.mag = n*mag;
		return sum;
	}
#endif // VEC_H_INCLUDED
