#include "Quad.h"
#include "Bitmap.h"
#include "stdafx.h"
#include <string>



Quad::Quad(float x1, float x2, float y1, float y2, float z1, float z2) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	this->z1 = z1;
	this->z2 = z2;

}


void Quad::TextureDetails(GLuint tex, float r1 = 0, float r2 = 0, float r3 = 0, float r4 = 0, float r5 = 0, float r6 = 0, float r7 = 0, float r8 = 0) {
	this->rep1 = r1;
	this->rep2 = r2;
	this->rep3 = r3;
	this->rep4 = r4;
	this->rep5 = r5;
	this->rep6 = r6;
	this->rep7 = r7;
	this->rep8 = r8;
	this->tex = tex;
}
void Quad::Draw() {

	glEnable(GL_TEXTURE_2D);

	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex);





	float m1_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m1_spe[] = { 0.0f, 0.0f,0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);

	glPushMatrix();
	glBegin(GL_QUADS);



	//koordynata tekstury - ile razy ma sie powtarzaæ np - 1.0f - rozciegnieta po ca³oœci. 10f - 10 tekstur powtórzonych.
	glTexCoord2f(rep1, rep2);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x1,y1,z1);

	glTexCoord2f(rep3, rep4);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x1, y2, z2);

	glTexCoord2f(rep5, rep6);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x2, y2, z2); 

	glTexCoord2f(rep7,rep8);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x2, y1, z1);

	glDisable(GL_TEXTURE_2D);


	glEnd();

}