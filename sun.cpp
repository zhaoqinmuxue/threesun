#include "stdafx.h"
#include "sun.h"

	Sun::Sun() {}
	Sun::Sun(Vec p, Vec v, double _mass, double _radius,double t,double b):NowPosition(p),PrePosition(p),InitPosition(p),
		velocity(v), mass(_mass), radius(_radius),temperature(t),brightness(b){}
	Sun::~Sun() {}

	void Sun::display()const
	{
		Vec* temp = new Vec(NowPosition - PrePosition);
		std::cout << "Position: " << NowPosition << "    " << "velocity: " << 
			temp->magval()/step << std::endl;
		delete temp;
	}
