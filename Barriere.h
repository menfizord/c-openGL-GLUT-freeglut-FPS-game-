///STATYCZNE OBJEKTY KTORE BEDA TYLKO STAC 
/// POPRAWKA: KLASA DO BARRIER BO JUZ NIE CHCE MI SIE NOWYCH PLIKOW ROBIC
#ifndef Barriere_H
#define Barriere_H
#include "stdafx.h"

class Barriere {
public:
	GLuint obj;
	GLuint tex;
	float deltaZ = 0; //przesuniecie po zecie 
	float deltaX = 0;// przesuniecie po X
	Barriere(GLuint, GLuint, float,float);
	void BarriereDraw();
};



#endif