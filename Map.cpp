#include "Map.h"
#include "stdafx.h"
#include "Bitmap.h"
#include "objLoader.h"
#include "Barriere.h"
#include "Monster.h"
Map::Map() {

	//texts = new std::vector<GLuint>();
	//Quads = new std::vector<Quad*>();
}
Map::~Map() {
	while (Barriers.size() != 0) {
		Barriers.pop_back();
	}
	for (int i = Quads.size(); i >= 0; i--) {
		for (int j = Quads[i].size(); i >= 0; i--) {
			Quads[i].pop_back();
		}
		Quads.pop_back();
	}
	while (Cars.size() != 0) {
		Cars.pop_back();
	}
}

void Map::makeQuads() {
	///


	///MOGÊ TO WSZYSTKO ZAMKN¥Æ W JEDNYM FORZE ALE TAK LEPIEJ WIDAC CO GDZIE JEST



	///
	//ULICA
	std::vector<Quad*> floor;
	for (float i = -9.68f; i > -20.32f; i -= 0.13) { //te wartosci to +- zeby by³o tak jak mialem pojedyncze quady i zebym objow nie musial przestawiac
													 //for (float j = 0.0f; j < 0.51f;j+=0.5f){
		Quad* street = new Quad(i, i - 0.13f, 0.0f, 0.0f, 0.0f, 1.0f); //ulica
		floor.push_back(street);
	}Quads.push_back(floor);

	//KRAWEZNIK PO LEWEJ I PRAWEJ PLASKA CZESC
	std::vector<Quad*> RCurbFlat;
	std::vector<Quad*> LCurbFlat;
	for (float i = -9.68f; i > -20.32f; i -= 0.13) {

		Quad* RCurb = new Quad(i, i - 0.13f, 0.02f, 0.02f, 1.00f, 1.02f); // PRAWA plaska czeœæ kraweznika
		Quad* LCurb = new Quad(i, i - 0.13f, 0.02f, 0.02f, 0.0f, -0.02f); // LEWA
		RCurbFlat.push_back(RCurb);
		LCurbFlat.push_back(LCurb);
	} 	Quads.push_back(RCurbFlat); Quads.push_back(LCurbFlat);

	//KRAWEZNIK PO LEWEJ I PRAWEJ PIONOWA CZESC
	std::vector<Quad*> RCurbPion; //nie pamietam jak jest pion po angielsku
	std::vector<Quad*> LCurbPion; //nie pamietam jak jest pion po angielsku
	for (float i = -9.68f; i > -20.32f; i -= 0.13) {

		Quad* RCurbP = new Quad(i, i - 0.13f, 0.0f, 0.02f, 1.00f, 1.0f); // plaska czeœæ kraweznika
		Quad* LCurbP = new Quad(i, i - 0.13f, 0.0f, 0.02f, 0.0f, 0.0f); // plaska czesc lewego
		RCurbPion.push_back(RCurbP);
		LCurbPion.push_back(LCurbP);
	} 	Quads.push_back(RCurbPion); Quads.push_back(LCurbPion);

	//CHODNIK PO PRAWEJ I LEWEJ STRONIE
	std::vector<Quad*> LSideWalk;
	std::vector<Quad*> RSideWalk;
	for (float i = -9.68f; i > -20.32f; i -= 0.13) {

		Quad* LChodnik = new Quad(i, i - 0.13f, 0.02f, 0.02f, 1.02f, 1.32f); // nazewnictwo mi sie zepsulo ...
		Quad* PChodnik = new Quad(i, i - 0.13f, 0.02f, 0.02f, -0.02f, -0.32f); // plaska czesc lewego
		LSideWalk.push_back(LChodnik);
		RSideWalk.push_back(PChodnik);
	} 	Quads.push_back(LSideWalk); Quads.push_back(RSideWalk);

	// SCIANA PO LEWEJ I PRAWEJ STRONIE
	std::vector<Quad*> LWallV;
	std::vector<Quad*> RWallV;
	for (float i = -9.68f; i > -20.32f; i -= 0.13) {

		Quad* LWall = new Quad(i, i - 0.13f, 0.02f, 0.82f, -0.32f, -0.32f); // Sciana lewo
		Quad* RWall = new Quad(i, i - 0.13f, 0.02f, 0.82f, 1.32f, 1.32f); // Sciana Prawo
		LWallV.push_back(LWall);
		RWallV.push_back(RWall);
	} 	Quads.push_back(LWallV); Quads.push_back(RWallV);

	///// murek bo nie moge nic znalezc zeby zablokowac chodnik 
	std::vector<Quad*> WallBlock1V;
	std::vector<Quad*> WallBlock2V;
	std::vector<Quad*> WallBlock3V;
	for (float i = -10.0f; i > -20.0f; i -= 0.13) {
		Quad* WallBlock1 = new Quad(i, i - 0.13f, 0.02f, 0.08f, -0.06f, -0.06f); // murek
		Quad* WallBlock2 = new Quad(i, i - 0.13f, 0.08f, 0.10f, -0.06f, -0.06f); // kraweznik murka
		Quad* WallBlock3 = new Quad(i, i - 0.13f, 0.1f, 0.1f, -0.06f, -0.12f);   // pionowa czesc murka
		WallBlock1V.push_back(WallBlock1);
		WallBlock2V.push_back(WallBlock2);
		WallBlock3V.push_back(WallBlock3);
	} 	Quads.push_back(WallBlock1V); Quads.push_back(WallBlock2V); Quads.push_back(WallBlock3V);

}
void Map::loadTexts() {
	// tekstury do "recznych" rzeczy
	 skyTex = LoadTexture("Resources\\Skydome.bmp", GL_LINEAR, GL_LINEAR);
	 backBuildingTex = LoadTexture("Resources\\BackBuilding2.bmp", GL_LINEAR, GL_LINEAR);
	 lampTex = LoadTexture("Resources\\metal.bmp", GL_LINEAR, GL_LINEAR);
	/////////////////////
	GLuint ulica = LoadTexture("Resources\\asphalt.bmp", GL_LINEAR, GL_LINEAR);
	texts.push_back(ulica);
	for (int i = 0; i < Quads[0].size(); i++) {
		Quads[0][i]->TextureDetails(ulica, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); //textura ulicy ///TO TROCHE TRICKI JUZ 
	}

	GLuint kraweznik = LoadTexture("Resources\\testchodnik.bmp", GL_LINEAR, GL_LINEAR);
	for (int i = 0; i < Quads[0].size(); i++) { //troche srednio ale wektory beda takiej samej wielkosci
		Quads[1][i]->TextureDetails(kraweznik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); //textura kraweznika
		Quads[2][i]->TextureDetails(kraweznik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); 
		Quads[3][i]->TextureDetails(kraweznik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
		Quads[4][i]->TextureDetails(kraweznik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	}



	GLuint chodnik = LoadTexture("Resources\\stones.bmp", GL_LINEAR, GL_LINEAR);
	for (int i = 0; i < Quads[0].size(); i++) { //troche srednio ale wektory beda takiej samej wielkosci
		Quads[5][i]->TextureDetails(chodnik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); //textura kraweznika
		Quads[6][i]->TextureDetails(chodnik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	}

	GLuint Lsciana = LoadTexture("Resources\\b1.bmp", GL_LINEAR, GL_LINEAR); //lewa sciana
	GLuint Psciana = LoadTexture("Resources\\windows_tower_block_3000.bmp", GL_LINEAR, GL_LINEAR);

	for (int i = 0; i < Quads[0].size(); i++) { //troche srednio ale wektory beda takiej samej wielkosci
		Quads[7][i]->TextureDetails(Lsciana, 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f); //textura kraweznika
		Quads[8][i]->TextureDetails(Psciana, 0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f);

	}

	GLuint blockwal1 = LoadTexture("Resources\\wall2.bmp", GL_LINEAR, GL_LINEAR);
	for (int i = 0; i < Quads[9].size(); i++) { //troche srednio ale wektory beda takiej samej wielkosci
		Quads[9][i]->TextureDetails(blockwal1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); //murek pionowa czesc wieksza
		Quads[10][i]->TextureDetails(kraweznik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); //pionowa czesc mniejsza
		Quads[11][i]->TextureDetails(chodnik, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f); // plaska czesc

	}



}
void Map::drawQuads() {
	for (int i = 0; i < Quads.size(); ++i) {
		for (int j = 0; j < Quads[i].size(); ++j) {
			Quads[i][j]->Draw();
		}
		
	}
	//przednia sciana biurowca bo zjeba³em cos robiac definiujac quady
#pragma region biurowiecPrzod
	{
		glEnable(GL_TEXTURE_2D);

		// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, backBuildingTex);
		float m1_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m1_spe[] = { 0.0f, 0.0f,0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);

	}
#pragma endregion
#pragma region biurowiecTyl
	{
		glEnable(GL_TEXTURE_2D);

		// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, backBuildingTex);
		float m1_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		float m1_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float m1_spe[] = { 0.0f, 0.0f,0.0f, 0.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, m1_amb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m1_dif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, m1_spe);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glBegin(GL_QUADS);
		for (float i = 0.0f; i < 0.72f; i += 0.1f) {

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-20.34f, i, -0.32f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-20.34f, i+0.1f, -0.32f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-20.34f, i + 0.1f, 1.32f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-20.34f, i, 1.32f);
		glEnd();


		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-9.68f, i, -0.32f);

		glTexCoord2f(0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-9.68f, i + 0.1f, -0.32f);

		glTexCoord2f(1.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-9.68f, i + 0.1f, 1.32f);

		glTexCoord2f(1.0f, 1.0f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-9.68f, i, 1.32f);
		glEnd();


		}
		
	}
#pragma endregion

}
void Map::LoadTextsToObj() {
	////////////////////////////////textury auta
	GLuint texCar1= LoadTexture("Resources\\czerwint.bmp", GL_LINEAR, GL_LINEAR);
	textsToObj.push_back(texCar1);
	GLuint texCar2 = LoadTexture("Resources\\ddd.bmp", GL_LINEAR, GL_LINEAR);
	textsToObj.push_back(texCar2);
	GLuint texCar3 = LoadTexture("Resources\\szaryt.bmp", GL_LINEAR, GL_LINEAR);
	textsToObj.push_back(texCar3);
	GLuint texCar4 = LoadTexture("Resources\\orenzt.bmp", GL_LINEAR, GL_LINEAR);
	textsToObj.push_back(texCar4);
	GLuint texCar5 = LoadTexture("Resources\\blektt.bmp", GL_LINEAR, GL_LINEAR);
	textsToObj.push_back(texCar5);
	///////////////////////////////////////////////////////
	GLuint barrierTex = LoadTexture("Resources\\BarrierTex.bmp", GL_LINEAR, GL_LINEAR);
	textsToObj.push_back(barrierTex);

}
void Map::loadObjects() {
	//GLuint tabOfCars[5];
	/// ZAPARKOWANE AUTA
	GLuint Cartex = LoadObj("Resources\\samochod.obj");
	for (int i = 0; i < 24;i+=1){
	Car*  car= new Car(Cartex, textsToObj[rand() % 5],(float)i*10); //10 to roznica zeby auta byly obok siebie
	Cars.push_back(car);
	}
	/// bariery
	GLuint Barriertex = LoadObj("Resources\\concrete_roadblock_02.obj");
	Barriere* Barrier = new Barriere(Barriertex, textsToObj[5], (float)0, (float)0);
	Barriers.push_back(Barrier);
	Barriere* Barrier2 = new Barriere(Barriertex, textsToObj[5], (float)0, (float)7);
	Barriers.push_back(Barrier2);
	Barriere* Barrier3 = new Barriere(Barriertex, textsToObj[5], (float)0, (float)14);
	Barriers.push_back(Barrier3);
	Barriere* Barrier4 = new Barriere(Barriertex, textsToObj[5], (float)260, (float)0);
	Barriers.push_back(Barrier4);
	Barriere* Barrier5 = new Barriere(Barriertex, textsToObj[5], (float)260, (float)7);
	Barriers.push_back(Barrier5);
	Barriere* Barrier6 = new Barriere(Barriertex, textsToObj[5], (float)260, (float)14);
	Barriers.push_back(Barrier6);




}
void Map::drawObjts() {
	for (int i = 0; i <Cars.size(); i++) {
		Cars[i]->carDraw();
	}
	for (int i = 0; i < Barriers.size(); i++) {
		Barriers[i]->BarriereDraw();
	}
}

void Map::drawLamps() {
	glEnable(GL_TEXTURE_2D);

	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, lampTex);
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation //STACKOVERFLOW NIE WIEM JAK TO DZIALA 
	glEnable(GL_TEXTURE_GEN_T);
	///lampa 1
	//stopka
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-12.0f, 0.07f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-12.0f, 0.44f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-12.0f, 0.44f, -0.03f);
	glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-5.97f, -0.003f, 0.06f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-6.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);
	glPopMatrix();
	///lampa2


	glPushMatrix();
	glTranslatef(-16.0f, 0.07f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-16.0f, 0.44f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-16.0f, 0.44f, -0.03f);
	glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-5.97f, -0.003f, 0.06f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-10.0f, 0.4f, 0.0f); 
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);
	glPopMatrix();


	///lampa 3
	//stopka

	glPushMatrix();
	glTranslatef(-12.0f, 0.07f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-12.0f, 0.44f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-12.0f, 0.44f, 1.03f);
	glRotatef(-225.0f, 1.0f, 0.0f, 0.0f);

	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-6.00f, -0.003f, 0.92f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-6.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);
	glPopMatrix();





	///lampa 4
	glPushMatrix();
	glTranslatef(-16.0f, 0.07f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-16.0f, 0.44f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-16.0f, 0.44f, 1.03f);
	glRotatef(-225.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-6.00f, -0.003f, 0.92f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-10.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);
	glPopMatrix();


	///lampa 5
	glPushMatrix();
	glTranslatef(-14.0f, 0.07f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-14.0f, 0.44f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-14.0f, 0.44f, 1.03f);
	glRotatef(-225.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-6.00f, -0.003f, 0.92f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-8.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);

	glPopMatrix();






	///lampa6


	glPushMatrix();
	glTranslatef(-14.0f, 0.07f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-14.0f, 0.44f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-14.0f, 0.44f, -0.03f);
	glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-5.97f, -0.003f, 0.06f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-8.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);
	glPopMatrix();


	///lampa7


	glPushMatrix();
	glTranslatef(-18.0f, 0.07f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-18.0f, 0.44f, 1.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-18.0f, 0.44f, 1.03f);
	glRotatef(-225.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-6.00f, -0.003f, 0.92f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-12.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);

	glPopMatrix();






	///lampa8


	glPushMatrix();
	glTranslatef(-18.0f, 0.07f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.015f, 0.015f, 0.05f, 32, 32);
	glPopMatrix();
	//faktyczna rura
	glPushMatrix();
	glTranslatef(-18.0f, 0.44f, -0.03f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.40f, 32, 32);
	glPopMatrix();
	//rura to trzymania lampy
	glPushMatrix();
	glTranslatef(-18.0f, 0.44f, -0.03f);
	glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	gluCylinder(quadratic, 0.01f, 0.01f, 0.08f, 32, 32);
	glPopMatrix();
	//cos co udaje zarowke
	glPushMatrix();
	glTranslatef(-5.97f, -0.003f, 0.06f);
	//glRotatef(75.0f, 1.0f, 0.0f, 1.0f);
	glTranslatef(-12.0f, 0.4f, 0.0f);
	glScalef(0.05f, 0.03f, 0.12f);
	glutSolidCube(1.0f);
	glPopMatrix();



	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
}
void Map::drawSky() {
	

	int Np = 36;
	float radius = 8.0f;
	
	
	glPushMatrix(); //TO NIE MOJ KOD !

	glEnable(GL_TEXTURE_2D);

	// Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, skyTex);
	glTranslatef(-16.0f, -3.0f, 0.0f);
	glBegin(GL_QUAD_STRIP);
	for (int j = -1; j < Np / 2; ++j) {
		for (int i = 0; i <= Np; ++i) {

			float t1 = PI * j / Np - PI / 2;
			float t2 = PI * (j + 1) / Np - PI / 2;
			float p = PI * 2.0f * i / Np;

			float tx1 = sin(t1) * cos(p);
			float tx2 = sin(t2) * cos(p);
			float tz1 = sin(t1) * sin(p);
			float tz2 = sin(t2) * sin(p);
			float ty1 = cos(t1);
			float ty2 = cos(t2);

			float tr1 = -sin(t1);
			float tr2 = -sin(t2);

			float x1 = radius * tx1;
			float x2 = radius * tx2;
			float z1 = radius * tz1;
			float z2 = radius * tz2;
			float y1 = radius * ty1;
			float y2 = radius * ty2;

			glTexCoord2f(.5f + .5f * tr2 * tx2, .5f + .5f * tr2 * tz2);
			glNormal3f(x2, y2, z2);
			glVertex3f(x2, y2, z2);
			glTexCoord2f((.5f + .5f * tr1 * tx1), .5f + .5f * tr1 * tz1);
			glNormal3f(x1, y1, z1);
			glVertex3f(x1, y1, z1);
			
		}
	}

	glEnd();





	//glTranslatef(5.0f, 0.0f, 0.0f);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

