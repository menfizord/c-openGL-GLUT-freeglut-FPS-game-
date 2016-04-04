#ifndef PlayerPanel_H
#define PlayerPanel_H
#include "stdafx.h"

class PlayerPanel {
private:
	GLuint tex;
public:
	PlayerPanel();
	void getTex(GLuint);
	void draw();
	void drawText(int,float);
	void drawCrosshair();


};



#endif 