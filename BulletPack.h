#ifndef BulletPack_H
#define BulletPack_H
#include "stdafx.h"

class BulletPack {
private:
	GLuint tex, obj;
	float x,z;
public:
	BulletPack(float, GLuint,GLuint);
	void draw();
	bool grab(float*);

	

};



#endif