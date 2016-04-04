#include "stdafx.h"
#include "BulletPack.h"


BulletPack::BulletPack(float mobDies,GLuint tex,GLuint obj) {
	this->x = mobDies;
	this->tex = tex;
	this->obj = obj;
	//z = float((10 + rand()%70) / 100);
	z = 0.5f;
}
void BulletPack::draw() {
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	//glDisable(GL_LIGHTING);
	//Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex);
	float m1_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m1_spe[] = { 0.0f, 0.0f,0.0f, 0.0f };


	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
	glTranslatef(x, 0.05f, z);
	glScalef(0.01f, 0.01f, 0.01f);

	double T = glutGet(GLUT_ELAPSED_TIME);
	float rot = T / 4.0f;
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
	glCallList(obj);
	glPopMatrix();
	glEnable(GL_FOG);
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}
bool BulletPack::grab(float* pos) {
	if ((x - pos[0]<0.2f || -x + pos[0] >0.2f) && (z - pos[2]<0.2f || -z + pos[2] >0.2f)) return true;
	else return false;
}