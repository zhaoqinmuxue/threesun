#include "stdafx.h"
#include <iostream>
#include "vec.h"
#include "sun.h"
#include "galaxy.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <windows.h>

using namespace std;

int main(int argc, char ** argv)
{
	Vec p1, v1, p2, v2, p3, v3;		//初位置和初速度矢量
	double m1, m2, m3;				//质量
	double t1, t2, t3, t4, t5, t6;		//暂时存储输入的临时变量
	int choice, t;							//选择
	cout << "欢迎来到三体世界" << endl;
	cout << "你可以自定义输入三体数据，另外我们也准备了五组特定数据供选择。" << endl
		<< "1: 8字形运动特解" << endl << "2: 日地月稳定系统" << endl << "3: 双恒星单行星系" << endl
		<< "4: 行进中的螺旋线" << endl << "5: 悲惨的混沌纪元" << endl << "6: 自定义位置、速度和质量" << endl
		<< "你的选择是：";
	cin >> choice;
	while (choice < 1 | choice > 6)
	{
		cout << "只能输入1-6的整数！" << endl;
		cout << "您的选择是：";
		cin >> choice;
	}
	//为免去输入的麻烦，这里给出了5组数据可以直接使用
	switch (choice)
	{
	case 1: p1 = { 194.000872, 0, -48.617506 }; v1 = { 18.6481474, 0, 17.2946292 };
			   p2 = { -194.000872, 0, 48.617506 }; v2 = { 18.6481474, 0, 17.2946292 };
			   p3 = { 0, 0, 0 }; v3 = { -37.2962948, 0, -34.5892584 };
			   m1 = 16; m2 = 16; m3 = 16;
			   break;
	case 2: p1 = { -6,0,0 }; v1 = { 0,0,2 };
			   p2 = { 365,-60,0 }; v2 = { 0,0,-100 };
			   p3 = {380,-50,0}; v3 = { 0,0,-170 };
			   m1 = 200; m2 = 4; m3 = 0.1;
			   break;
	case 3: p1 = { -190,30,0 }; v1 = { 0,0,32.2 };
			   p2 = { 250,-30,0 }; v2 = { 0,0,-40 };
			   p3 = { 331,0,0 }; v3 = { 0,0,-200 };
			   m1 = 100; m2 = 80; m3 = 0.1;
			   break;
	case 4: p1 = { 50,100,-300 }; v1 = { 100,0,10 };
			p2 = { 60,50,-300 }; v2 = { -100,0,10 };
			p3 = { 50,200,-300 }; v3 = { -130,0,0 };
			m1 = 60; m2 = 60; m3 = 0.1;
			break;
	case 5: p1 = { -40,10,0 }; v1 = { 0,0,90 };
			p2 = { 50,-10,0 }; v2 = { 0,0,-90 };
			p3 = { 120,66,0 }; v3 = { 0,0,-90 };
			m1 = 80; m2 = 50; m3 = 30;
			break;
	//自定义输入会很长
	case 6: cout << "第一个星球的坐标（三个参数）（0-500）: ";
		       cin >> t1 >> t2 >> t3; p1 = {t1,t2,t3};
			   cout << "第一个星球的速度（三个参数）（0-500）: ";
			   cin >> t1 >> t2 >> t3; v1 = {t1,t2,t3};
			   cout << "第一个星球的质量（一个参数）（0-500）："; cin >> m1;
			   cout << "第二个星球的坐标（三个参数）（0-500）: ";
			   cin >> t1 >> t2 >> t3; p2 = { t1,t2,t3 };
			   cout << "第二个星球的速度（三个参数）（0-500）: ";
			   cin >> t1 >> t2 >> t3; v2 = { t1,t2,t3 };
			   cout << "第二个星球的质量（一个参数）（0-500）："; cin >> m1;
			   cout << "第三个星球的坐标（三个参数）（0-500）: ";
			   cin >> t1 >> t2 >> t3; p3 = { t1,t2,t3 };
			   cout << "第三个星球的速度（三个参数）（0-500）: ";
			   cin >> t1 >> t2 >> t3; v3 = { t1,t2,t3 };
			   cout << "第三个星球的质量（一个参数）（0-500）："; cin >> m1;
			   break;
	}
	//默认三颗星球到原点的温度和亮度都是100，为了简化和时间问题没有再弄一个相对某个位置的亮度和温度
	cout << "温度和亮度是否使用默认100（1是，0不是）";
		cin >> t1;
		if (t1 == 0)
		{
			cout << "三颗星球在原点的初始温度（大于0）：";
			cin >> t1, t2, t3;
			cout << "三颗星球在原点的初始亮度（大于0）";
			cin >> t4, t5, t6;
		}
		else { t1 = t2 = t3 = t4 = t5 = t6 = 100; }
		//时间太短容易一闪而过，太长会跑很久
		cout << "模拟多长时间的结果（单位：s，建议一万到一千万）：";
			cin >> t;
	glutInit(&argc, argv);				//初始化opengl和窗口，其他函数因为参数传递的问题移到了galaxy.cpp中
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("三体模拟");

	Sun sun[3] = { Sun(p1*P,v1,m1,1,t1,t4),Sun(p2*P,v2,m2,1,t2,t5),Sun(p3*P,v3,m3,1,t3,t6) };
	Galaxy galaxy(sun, t);
	galaxy.simulate();
	return 0;
}
