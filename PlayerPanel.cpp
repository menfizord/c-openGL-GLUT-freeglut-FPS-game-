#include "stdafx.h"
#include "PlayerPanel.h"


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


PlayerPanel::PlayerPanel() {
	;
}
void PlayerPanel::getTex(GLuint tex) {
	this->tex = tex;
}
void PlayerPanel::draw() {

	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	//Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();

	//
	glBegin(GL_QUADS);
	//NIE RUSZAC TEGO GOWNA JUZ NIECH TAK ZOSTANIE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JESZCZE MNIEJSZE TE FLOATY 
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.103f, -0.03f, -0.1f);

	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.103f, -0.058f, -0.1f);

	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, -0.058f, -0.1f);

	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, -0.03f, -0.1f);


	glEnd();



	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
}
void PlayerPanel::drawText(int bullets,float fog) {
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	cout << "bullets:" << bullets<<endl;
	glPushMatrix();
	char string[30] = {};
	_snprintf(string, 30, "Bullets left: %d",bullets);
	Print2(-0.1f, -0.04f, string);
	_snprintf(string, 30, "Dipresed Fog: %.2f/100%c", fog,'%');
	Print2(-0.1f, -0.05f, string);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
}
void PlayerPanel::drawCrosshair() {
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0003f, -0.1f);
	glVertex3f(0.0f, 0.002f, -0.1f);

	glVertex3f(0.0f, -0.0003f, -0.1f);
	glVertex3f(0.0f, -0.002f, -0.1f);

	glVertex3f(-0.002f, 0.0f, -0.1f);
	glVertex3f(-0.0003f, 0.0f, -0.1f);


	glVertex3f(0.0003f, 0.0f, -0.1f);
	glVertex3f(0.002f, 0.0f, -0.1f);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
}