#include "stdafx.h"
#include "galaxy.h"
#include <iostream>

Sun Galaxy::sun[3];	//静态成员函数需定义一边
int Galaxy::time;
int B = 500;		//投影到坐标系上的缩小比例

//初始化
void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		//确定清屏颜色
	glClear(GL_COLOR_BUFFER_BIT);		//清屏
	glMatrixMode(GL_MODELVIEW);	
	gluLookAt(5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);		//观察点的位置，这里设成了第一象限中央，不能移动
	glMatrixMode(GL_PROJECTION);		//透视模式
	glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 8.0f, 10.0f);		//设定视野范围
}

void Galaxy::display()
{
	init();
	glLineWidth(1.0f);
	glPointSize(3.0f);
	for (double j = step; j < time; j += step)			//计算下一时刻位置
	{
		Vec distance01 = sun[1].NowPosition - sun[0].NowPosition;						//计算相对位置矢量
		double n01 = G*sun[1].mass*sun[0].mass / pow(distance01.magval(), 3);	//计算受力和相对位置的比例关系
		Vec distance02 = sun[2].NowPosition - sun[0].NowPosition;
		double n02 = G*sun[2].mass*sun[0].mass / pow(distance02.magval(), 3);
		Vec distance12 = sun[2].NowPosition - sun[1].NowPosition;
		double n12 = G*sun[2].mass*sun[1].mass / pow(distance12.magval(), 3);
		Vec a[3];
		a[0] = distance01*(n01 / sun[0].mass) + distance02*(n02 / sun[0].mass);		//以相对位置矢量的方向为基础求加速度
		a[1] = distance01.contrary()*(n01 / sun[1].mass) + distance12*(n12 / sun[1].mass);
		a[2] = distance02.contrary()*(n02 / sun[2].mass) + distance12.contrary()*(n12 / sun[2].mass);
		for (int i = 0; i < 3; i++)
		{
			Vec temp = sun[i].PrePosition;
			sun[i].PrePosition = sun[i].NowPosition;
			sun[i].NowPosition = sun[i].PrePosition * 2 - temp + a[i] * pow(step, 2);		//计算下一时刻位置的公式
																															//当前位置，之前位置和加速度求新位置
		}
		if ((int)j % 500 == 0)			//减小计算负担，每500秒画一次运动图象，本来打算根据输入时间确定间隔大小更好地适应小数据和大数据
												//但是在数据太大时不知道为什么会崩溃
		{
			std::cout << j;				//每隔500秒显示当前星球状态和温度、亮度
			NowStatus();
			Sleep(20);						//暂停20ms，防止飞速运动看不清楚
			glClear(GL_COLOR_BUFFER_BIT);			//绘制坐标轴，蓝色为x轴，黄色y轴，紫色z轴，带小白点的是正方向
			glBegin(GL_LINES);
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glColor3f(1.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
			glEnd();
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_POINTS);				//画三颗星球，直接用小白点表示，比较简陋
			glVertex3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
			glVertex3f(sun[0].NowPosition.xval() / P / B, sun[0].NowPosition.yval() / P / B, sun[0].NowPosition.zval() / P / B);
			glVertex3f(sun[1].NowPosition.xval() / P / B, sun[1].NowPosition.yval() / P / B, sun[1].NowPosition.zval() / P / B);
			glVertex3f(sun[2].NowPosition.xval() / P / B, sun[2].NowPosition.yval() / P / B, sun[2].NowPosition.zval() / P / B);
			glEnd();
			glFlush();
			glutSwapBuffers();
		}
	}
	std::cout << time;
	NowStatus();
}


	Galaxy::Galaxy() {}
	Galaxy::Galaxy(Sun* V, int t)
	{
		sun[0] = V[0];
		sun[1] = V[1];
		sun[2] = V[2];
		time = t;
	}

	void Galaxy::calfirst()										//根据初时刻计算第二个时刻位置，有两个数据才能代入上面的公式迭代
	{
		Vec distance01 = sun[1].NowPosition - sun[0].NowPosition;
		double n01 = G*sun[1].mass*sun[0].mass / pow(distance01.magval(), 3);
		Vec distance02 = sun[2].NowPosition - sun[0].NowPosition;
		double n02 = G*sun[2].mass*sun[0].mass / pow(distance02.magval(), 3);
		Vec distance12 = sun[2].NowPosition - sun[1].NowPosition;
		double n12 = G*sun[2].mass*sun[1].mass / pow(distance12.magval(), 3);
		Vec a[3];
		a[0] = distance01*(n01 / sun[0].mass) + distance02*(n02 / sun[0].mass);
		a[1] = distance01.contrary()*(n01 / sun[1].mass) + distance12*(n12 / sun[1].mass);
		a[2] = distance02.contrary()*(n02 / sun[2].mass) + distance12.contrary()*(n12 / sun[2].mass);
		for (int i = 0; i < 3; i++)
		{
			sun[i].NowPosition = sun[i].PrePosition + sun[i].velocity*step + a[i] * (pow(step, 2)*0.5);	//速度、加速度求位置
		}
	}

	void Galaxy::NowStatus()							//计算亮度和温度，亮度和距离的二次方成反比，温度和距离的三次方成反比																
	{																//当分母为0时取为1
		double d0 = sun[0].NowPosition.magval();
		if (d0 == 0) d0 = 1;
		double d1 = sun[1].NowPosition.magval();
		if (d1 == 0) d1 = 1;
		double d2 = sun[2].NowPosition.magval();
		if (d2 == 0) d2 = 1;
		std::cout << "s:		temperature: " << pow(sun[0].InitPosition.magval() / d0, 3)*sun[0].temperature +
			pow(sun[1].InitPosition.magval() / d1, 3)*sun[1].temperature +
			pow(sun[2].InitPosition.magval() / d2, 3)*sun[2].temperature
			<< "   brightness: " << pow(sun[0].InitPosition.magval() / d0, 2)*sun[0].brightness +
			pow(sun[1].InitPosition.magval() / d1, 2)*sun[1].brightness +
			pow(sun[2].InitPosition.magval() / d2, 2)*sun[2].brightness << std::endl;
		for (int i = 0; i < 3; i++)
			sun[i].display();
	}

	void Galaxy::simulate()
	{
		calfirst();										//计算第一步
		glutDisplayFunc(display);				//逐步迭代并画图
		glutMainLoop();							//无限循环上一步
	}
