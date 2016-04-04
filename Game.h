#ifndef Game_H
#define Game_H
#include "stdafx.h"
#include "PlayerPanel.h"
#include "BulletPack.h"
class Game {
private:
	Map* mapa; //includes cars barriers terrain etc
	GLuint monsterTex, monsterObj,playerPanelTex,BulletTex,BulletObj;
	float* playerPos; //array of player cords
	int timertoSpawnMob = 0; //counter of time to spawn a monster
	float fog = 1.0f;  // 
	float stances[7] = { 240.0f, 206.0f ,177.0f,147.0f,117.0f,88.0f,59.0f}; //240 to krotnoœæ 17 tak ¿e jest oko³o 4 sec 206 3,5sec 177 3 sec itd ...
	PlayerPanel* playerPanel;
	GLuint startScreen,winScreen,LoseScreen;
	int dieCount = 0; // to spawn bulletpack every n mob
	
public:
	enum GameState { start, playing, dead, win }; //musi byc publiczne bo bede to setowa³ z miejsc gdzie nie bedzie obiektu gracza
	Player* player;
	Game();
	~Game();
	GameState gameState;
	void loadObjs();
	void loadTexts();
	void otherPreparationThings();
	void draw();
	void drawOnFront();
	void drawMobs();
	void drawBulletPacks();
	std::vector<Monster*> Mobs;
	std::vector<BulletPack*> bulletPack;
	void makeMob();
	void getPlayerPos(float,float,float);
	void deletingMobs();
	float getFog();
	float calucaltePercentOfFog();
	void setState(GameState);
	void drawStartScreen(GLuint);
	void restartGame();
	void Grab(); //delete obj if grabed
};

#endif 