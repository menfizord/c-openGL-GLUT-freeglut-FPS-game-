#pragma once
#ifndef Car_H
#define Car_H
#include "stdafx.h"

class Car {
public:
	GLuint obj;
	GLuint tex;
	
	float deltaZ=0; //przesuniecie po zecie 
	Car(GLuint, GLuint,float);
	void carDraw();
};


#endif