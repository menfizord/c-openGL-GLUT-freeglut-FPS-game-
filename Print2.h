
#ifndef Print2_H
#define Print2_H



/// JUZ NIE CHCE MI SIE ROBIC OSOBNEGO CPP DLA TEJ FUNKCJI
#include "stdafx.h"
void Print2(float x, float y, const char *string)
{
	glDisable(GL_TEXTURE_2D);
	int len, i;
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos3f(x, y, -0.1f);

	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	glEnable(GL_TEXTURE_2D);
}


#endif 