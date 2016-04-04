

#ifndef Quad_H
#define Quad_H

#include "stdafx.h"

class Quad{
protected:
	float x1, x2, y1, y2, z1, z2; //cords of points to make quad
	float rep1, rep2,rep3,rep4,rep5,rep6,rep7,rep8; // how many textures in z and x (moze za duzo ale juz nie jestem pewien)
	GLuint tex;
	
public:
	 Quad(float x1, float x2, float y1, float y2, float z1, float z2);
	 ~Quad();
	 void TextureDetails(GLuint, float, float, float, float, float, float, float, float);
	 void Draw();
};

#endif // !Quad_H
