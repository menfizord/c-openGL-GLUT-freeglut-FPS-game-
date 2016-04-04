#include "stdafx.h"
#include "Barriere.h"
#include "Bitmap.h"
#include "objLoader.h"

Barriere::Barriere(GLuint obj, GLuint text, float deltaZ,float deltaX) {
	this->obj = obj;
	this->tex = text;
	this->deltaZ = deltaZ;
	this->deltaX = deltaX;
}
void Barriere::BarriereDraw() {

	glEnable(GL_TEXTURE_2D);

	//Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();
	float m1_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m1_spe[] = { 0.0f, 0.0f,0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

	glScalef(0.035f, 0.035f, 0.035f); //to na czuja 

	glTranslatef(-19.0f + this->deltaX, 0.0f, -560.0f + this->deltaZ); //490 pkt startowy nie wiem dlaczego akurat tyle ale tak wyglada git
	glCallList(obj);
	glPopMatrix();




	glDisable(GL_TEXTURE_2D);
}

