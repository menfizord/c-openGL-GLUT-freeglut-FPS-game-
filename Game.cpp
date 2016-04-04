#include "Game.h"
#include "stdafx.h"
#include "objLoader.h"



Game::Game() {
	mapa = new Map();
	player = new Player();
	playerPos = new float[3];
	playerPanel = new PlayerPanel();
	gameState = start;
}

	
void Game::loadObjs() {
	player->LoadPlayerObj();
	mapa->loadObjects();
	monsterObj = LoadObj("Resources\\minimob.obj");
	BulletObj = LoadObj("Resources\\pocisk.obj");
}
void Game::otherPreparationThings() {
	mapa->makeQuads();
}
void Game::loadTexts() {
	player->LoadTex();
	mapa->loadTexts();
	mapa->LoadTextsToObj();
	monsterTex = LoadTexture("Resources\\Monster.bmp", GL_LINEAR, GL_LINEAR);
	playerPanelTex= LoadTexture("Resources\\layout3.bmp", GL_LINEAR, GL_LINEAR);
	playerPanel->getTex(playerPanelTex);
	startScreen= LoadTexture("Resources\\tloT.bmp", GL_LINEAR, GL_LINEAR);
	winScreen = LoadTexture("Resources\\win2.bmp", GL_LINEAR, GL_LINEAR);
	LoseScreen = LoadTexture("Resources\\przegrana.bmp", GL_LINEAR, GL_LINEAR);
	BulletTex = LoadTexture("Resources\\Bullet.bmp", GL_LINEAR, GL_LINEAR);
}
void Game::draw() {
	if (gameState == playing) {
		mapa->drawLamps();
		mapa->drawObjts();
		mapa->drawQuads();
		mapa->drawSky();
		player->drawBullets();
		drawBulletPacks();
	}
}
void Game::drawOnFront() {
	if(gameState==start)
	drawStartScreen(startScreen);
	else if(gameState==playing){

		playerPanel->drawCrosshair();
		playerPanel->drawText(player->getBulletCount(), calucaltePercentOfFog()); // imo to odwrotna kolejnosæ ale spoko ...
		playerPanel->draw();
		player->Draw();
		
	}
	else if (gameState == win) {
		drawStartScreen(winScreen);
	}
	else drawStartScreen(LoseScreen);

}
Game::~Game() {
	delete mapa;
	delete player;
	delete[] playerPos;
	delete playerPanel;
	while (bulletPack.size() > 0) {
		bulletPack.pop_back();
	}
	while (Mobs.size() > 0) {
		Mobs.pop_back();
	}

}
void Game::drawMobs() {
	if (gameState == playing) {
		for (int i = 0; i < Mobs.size(); i++) {
			Mobs[i]->draw();
		}
	}
}
void Game::makeMob() {
	if (gameState == playing) {
		timertoSpawnMob++;
		int cap = 0;
		if (fog < 1.5f)cap = stances[0];
		else if (fog > 1.5f&&fog < 2.0f) cap = stances[1];
		else if (fog > 2.0f&&fog < 2.5f) cap = stances[2];
		else if (fog > 2.5f&&fog < 3.0f) cap = stances[3];
		else if (fog > 3.0f&&fog < 3.5f) cap = stances[4];
		else if (fog > 3.5f&&fog < 4.3f) cap = stances[5];
		else cap = stances[6];

		if (timertoSpawnMob == cap || Mobs.size() == 0) {
			Monster* monster = new Monster(monsterObj, monsterTex, playerPos[0]);
			Mobs.push_back(monster);
			timertoSpawnMob = 0;
		}

	}
}

void Game::getPlayerPos(float x,float y,float z) {
	this->playerPos[0] = x;
	this->playerPos[1] = y;
	this->playerPos[2] = z;
	if (gameState == playing) {
		///przy okazji usuwam tutaj moby jezeli zostaly zastrzelone
		int t = 0;
		int col = 0;
		if (Mobs.size() != 0) {
			for (int i = 0; i < Mobs.size(); i++) {
				Mobs[i]->getPlayerPos(x);
				col = Mobs[i]->checkPlayerCol(); //sprawdzanie kolizji z graczem	
				if (col == 1) gameState = dead;
			}
		}
	}
}
void Game::deletingMobs() {
	if (gameState == playing) {
		int t = 0;
		if (Mobs.size() != 0) {
			for (int i = 0; i < Mobs.size(); i++) {
				t = Mobs[i]->checkCol(player->getBullets());
				if (t == 1) {
					dieCount += 1;
					if(dieCount==4){
					BulletPack* bullets = new BulletPack(Mobs[i]->getDeadPos(), BulletTex, BulletObj);
					bulletPack.push_back(bullets);
					}
					std::swap(Mobs[i], Mobs[Mobs.size() - 1]); // z wektorow nie mozna usuwac ze srodka ...
					Mobs.pop_back();
					fog += 0.075f;

				}
			}
		}
	}
	if (dieCount == 4)dieCount = 0;
}
float Game::getFog() {
	return fog;
}
float Game::calucaltePercentOfFog() {
		//wygrana jak mgla bedzie 5.5f
	if (100 * (fog - 1.0f) / 4.5f>99 && 100 * (fog - 1.0f) / 4.5f<101) gameState = win;
	return 100*(fog - 1.0f) / 4.5f;
}
void Game::setState(Game::GameState state) {
	this->gameState = state;
}
void Game::drawStartScreen(GLuint tex) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	//Ustawienie sposobu teksturowania - GL_MODULATE sprawia, ¿e œwiat³o ma wp³yw na teksturê; GL_DECAL i GL_REPLACE rysuj¹ teksturê tak jak jest
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();

	//
	glBegin(GL_QUADS);
	//NIE RUSZAC TEGO GOWNA JUZ NIECH TAK ZOSTANIE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JESZCZE MNIEJSZE TE FLOATY 
	glTexCoord2f(0.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.11f, 0.058f, -0.1f);

	glTexCoord2f(0.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.11f, -0.058f, -0.1f);

	glTexCoord2f(1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.11f, -0.058f, -0.1f);

	glTexCoord2f(1.0f, 1.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.11f, 0.058f, -0.1f);


	glEnd();
	glEnable(GL_LIGHTING);
	glEnable(GL_FOG);
	glDisable(GL_TEXTURE_2D);
	glutSetCursor(GLUT_CURSOR_NONE);

}
void Game::restartGame() {

	player->restart();
	fog = 1.0f;
	timertoSpawnMob = 0;
	while (Mobs.size() != 0) {
		Mobs.pop_back();
	}
	while (bulletPack.size() != 0) {
		bulletPack.pop_back();
	}
	gameState = playing;
}
void Game::drawBulletPacks() {
	if (bulletPack.size() != 0) {
		for (int i = 0; i < bulletPack.size(); i++) {
			bulletPack[i]->draw();
		}
	}
}
void Game::Grab() {
	if (bulletPack.size() > 0) {
		for (int i = 0; i < bulletPack.size(); i++) {
			if (bulletPack[i]->grab(playerPos)) {
				std::swap(bulletPack[i], bulletPack[bulletPack.size() - 1]); // z wektorow nie mozna usuwac ze srodka ...
				bulletPack.pop_back();
				player->addBullets();
			}
		}
	}
}