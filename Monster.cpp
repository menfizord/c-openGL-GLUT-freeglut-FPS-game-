#include "Monster.h"
#include "stdafx.h"
#include <ctime>
#include "Bullet.h"


Monster::Monster(GLuint obj, GLuint tex, float pos) {
	this->obj = obj;
	this->tex = tex;
	playerPos = pos;


	if (playerPos + 2.5f > -9.5f) startingPos = -19.6f;
	else if((playerPos - 2.5f)< -19.6f) startingPos = -9.5f;
	else (rand() % 10) % 2 == 0 ? startingPos = -19.6f : startingPos = -9.5f;
	


	actualPos = startingPos;

	startingPos == -9.5f ? endingPos = -19.6f : endingPos = -9.5f;

}
void Monster::draw() {
	if (change == 0) {

		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, tex);
		if (this->dead && !this->stopMoving) {
			this->stopPosition = actualPos;
			this->stopMoving = true;
		}
		if (this->dead) {
			glTranslatef(stopPosition, -3.3f - flyOut, 0.5f);
			this->flyOut -= 0.005f;
			if (flyOut < -0.4f) timeToDelete = true;
	
				
		}
		if (!dead)glTranslatef(actualPos, -3.3f, 0.5f);

		///ROTACJA WZGLEM POLOZENIA DO GRACZA
		this->actualPos > this->playerPos ? glRotatef(-90.0f, 0.0f, 1.0f, 0.0f) : glRotatef(90.0f, 0.0f, 1.0f, 0.0f);


		glCallList(obj);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();



		if(!dead)calculateActualPos();

		//if (dead) {
		//	float x, y, z;
		//	x = y = z = 0.0f;
		//	glDisable(GL_LIGHTING);
		//	float przesuniecie, actual; //NIE WIEM JAK JEST PRZESUNIECIE PO ANGIELSKU ,,,,,,,,, przsuniecie bo model jest przesuniety i trzeba go skorygowac
		//	this->actualPos > this->playerPos ? przesuniecie = -0.2f : przesuniecie = +0.2f;
		//	actual = actualPos + przesuniecie;
		//	for (int i = 0; i < 10; i++) {
		//		i & 2 == 0 ? x = actual + (float)(i / 10.0f) : x = actual - (float)(i / 10.0f);
		//		for (int j = 0; j < 10; j++) {
		//			j % 2 == 0 ? y = 0.3f + (float)(j+i / 10.0f) : y = 0.3f - (float)(j+i / 10.0f);
		//			for (int k = 1; k < 7; k++) {
		//				//i & 2 == 0 ? x = actual + (float)(i/10.0f) : x=actual - (float)(i /10.0f);
		//				//j % 2 == 0 ? y = 0.3f + (float)(j / 10.0f) : y = 0.3f - (float)(j / 10.0f);
		//				k % 2 == 0 ? z = 0.5f + (float)(k+i+j / 10.0f) : z = 0.5f - (float)(k+i+j / 10.0f);
		//				glPushMatrix();
		//				glTranslatef(x, y, z);
		//				glutSolidCube(0.002f);
		//				glPopMatrix();

		//			}
		//		}
		//	}
		//	glEnable(GL_LIGHTING);
		//}
	}
}

void Monster::calculateActualPos() {
	this->actualPos -= (startingPos - endingPos) / 2000; 
}
void Monster::getPlayerPos(float pos) {
	this->playerPos = pos;
}
int Monster::checkCol(std::vector<Bullet*> bullets) { //TO JEST BARDZO BRZYDKIE ALE JAK BEDZIE ZAMULAC TO PRZEKAZE PRZEZ WSKAZNIK
	if(!dead){ //jak dead to juz "nie dostaje" kulkami
	float przesuniecie, actual; //NIE WIEM JAK JEST PRZESUNIECIE PO ANGIELSKU ,,,,,,,,, przsuniecie bo model jest przesuniety i trzeba go skorygowac
	this->actualPos > this->playerPos ? przesuniecie = -0.2f : przesuniecie = +0.2f;
    actual = actualPos + przesuniecie;
	///KOLIZJA Z POCISKIEM
	if (bullets.size() != 0 ) {
		
		
		for (int i = 0; i < bullets.size(); i++) {
			float* BulletPos = bullets[i]->getActualPos();
			if (BulletPos[0] < (actual + 0.15f) && BulletPos[0] > (actual - 0.15f) &&
				BulletPos[1] < 0.3f		             &&  BulletPos[1] > 0.1f && //YGEKI SIE NIE ZMIENIAJA 
				BulletPos[2] < 0.6f					 &&  BulletPos[2] > 0.4f    //ZTY te¿
				){ 
				this->dead = true;
				bullets[i]->hit();
				break;
			}
			else continue;
		}

	}
	}
	return timeToDelete ? 1 : 0;

}
int Monster::checkPlayerCol() {
	if (((actualPos - playerPos) < 0.2f && startingPos == -9.5f || startingPos == -19.6f && (playerPos - actualPos) < 0.2f )&&!dead) {
		return 1;
	}
	return 0;
}
float Monster::getDeadPos() {
	return stopPosition;
}
