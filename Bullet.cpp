#include "Bullet.h"
#include "stdafx.h"

Bullet::Bullet(float x, float y, float z, float dx, float dy,float dz) {
	start = new float[3];
	end = new float[3];
	start[0] = x + dx / 10;
	start[1] = y + dy / 10;
	start[2] = z + dz / 10;
	end[0] = x + 2.5f*dx;
	end[1] = y + 2.5f*dy;
	end[2] = z + 2.5f*dz;
	actual = new float[3];
	actual[0] = start[0];
	actual[1] = start[1];
	actual[2] = start[2];

}
void Bullet::draw() {
			glPushMatrix();
			glTranslatef(actual[0], actual[1], actual[2]);
			glutSolidSphere(0.002f, 16, 16);
			glPopMatrix();
			calculatePos();	
}
Bullet::~Bullet() {
	delete[] start;
	delete[] end;
	delete[] actual;
}

void Bullet::calculatePos() {

	actual[0] += ((end[0] - start[0]) /bulletSpeed);
	actual[1] += ((end[1] - start[1]) /bulletSpeed);
	actual[2] += ((end[2] - start[2]) /bulletSpeed);
	if (((start[0] - actual[0]) > range) || ((start[1] + actual[1]) > range) || ((start[1] - actual[1]) > range) ||
		((start[2] - actual[2]) > range) || ((actual[0] - start[0]) > range) || ((actual[1] - start[1]) > range)||
		accurate ) { //JAKBY CO TO MOGE TO ROZRYSOWAC
		this->state = 1; //1 przelecial swoje
	}
	else this->state = 0;

}
int Bullet::getState() {
	return this->state;
}
float* Bullet::getActualPos() {
	return actual;
}
void Bullet::hit() {
	accurate = true;
}