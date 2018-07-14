#ifndef GALAXY_H_INCLUDED
#define GALAXY_H_INCLUDED

#include "stdafx.h"
#include "sun.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <windows.h>
#define G 200000000		//万有引力常数乘以质量的一个放大倍数，在这里试了好多数值，最后发现这个比较拟合现实
#define P 10000				//对位置的放大倍数，这里没有放大速度，放大了位置，也是为了拟合真实情况，现实星星的距离真的非常远

	class Galaxy
	{
	private:
		static Sun sun[3];
		static int time;
	public:
		Galaxy();
		Galaxy(Sun* V, int t);
		static void NowStatus();
		void calfirst();
		void simulate();
		static void display();		//为了能画图，把display设成了静态成员函数，代价是成员变量也只能变成静态，不过其实也只模拟一次，没有影响
	};

#endif // GALAXY_H_INCLUDED
