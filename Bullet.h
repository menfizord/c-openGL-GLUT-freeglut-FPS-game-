#ifndef Bullet_H
#define Bullet_H
#include "stdafx.h"

class Bullet {
private:
	float* start;//STARTING PLACE
	float* end;	 // ENDING PLACE
	float* actual; 
	float range = 2.5f;
	void calculatePos(); //calculating actual position of bullet
	float dX=0, dY=0, dZ=0;
	float bulletSpeed=100.0f; //1/bulletspeed
	int state = 0; //0 ok 1 delete obj
	bool accurate = false;
public:
	Bullet(float, float, float,float,float,float);
		~Bullet();
	void draw();
	int getState();
	float* getActualPos();
	void hit();
};


#endif 