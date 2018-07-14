ifndef SUN_H_INCLUDED
#define SUN_H_INCLUDED

#include "stdafx.h"
#include "vec.h"

	class Sun
	{
	public:
		Vec NowPosition;			//因为计算公式的原因需要用到当前位置和上一个时刻的位置计算下一时刻的位置
		Vec PrePosition;
		Vec InitPosition;			//保存初始坐标用来计算亮度和温度
		Vec velocity;					//速度
		double mass;				//质量
		double radius;				//半径，可以用来判断是否相撞
		double temperature;		//温度
		double brightness;		//亮度
	public:
		Sun();
		Sun(Vec p, Vec v, double _mass, double _radius,double t,double b);
		~Sun();
		void display()const;		//输出当前状态
	};

#endif // SUN_H_INCLUDED
