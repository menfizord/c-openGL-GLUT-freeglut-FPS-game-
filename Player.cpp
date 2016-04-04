#include "Player.h"
#include "stdafx.h"
#include "objLoader.h"
#include "Bitmap.h"

Player::Player() {
	;
}
void Player::LoadPlayerObj() {
	this->obj = LoadObj("Resources\\m4a1.obj");
}
void Player::LoadTex() {
	tex = LoadTexture("Resources\\m42.bmp", GL_LINEAR, GL_LINEAR);
}
void Player::Draw() {
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
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

	glTranslatef(0.07f, -0.1f, 0.02f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	//glRotatef(90.0f,0.0f, 1.0f, 0.0f);

	glScalef(0.005f, 0.005f, 0.005f);
	//glutSolidCube(0.5f);
	glCallList(obj);


	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_FOG);

}
void Player::Shoot(float x, float y, float z, float dx, float dy,float dz) {
	//this->playerX = x;
	if (bullets > 0) {
	Bullet* bullet = new Bullet(x,y,z,dx,dy,dz);
	Bullets.push_back(bullet);
	bullets--;
	}
}
void Player::drawBullets() {
	for (int i = 0; i < Bullets.size(); i++) {
		Bullets[i]->draw();
		if (Bullets[i]->getState() == 1) {
			std::swap(Bullets[i], Bullets[Bullets.size() - 1]); // z wektorow nie mozna usuwac ze srodka ...
			Bullets.pop_back();
		}
	}
}
std::vector<Bullet*> Player::getBullets() {
	return Bullets;
}


int Player::getBulletCount() {
	return bullets;
}
Player::~Player() {
	while (Bullets.size() != 0) {
		Bullets.pop_back();
	}
}
void Player::restart() {
	while (Bullets.size() != 0) {
		Bullets.pop_back();
	}
	bullets = 8;
}

void Player::addBullets() {
	bullets += 5;
}