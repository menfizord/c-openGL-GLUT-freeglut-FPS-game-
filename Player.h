#ifndef Player_H
#define Player_H
#include "stdafx.h"
#include <vector>
#include "Bullet.h"
class Player {
private:
	GLuint obj;
	GLuint tex;
	std::vector<Bullet*> Bullets;
	int bullets = 8; // u need 60 bullets to win a game
	float playerX; //  to check if player moves
	int shotLive = 100;
public:
	Player();
	~Player();
	void LoadPlayerObj();
	void LoadTex();
	void Draw();
	void Shoot(float,float,float,float,float,float);
	void drawBullets();
	std::vector<Bullet*> getBullets();
	int getBulletCount();
	void restart();
	void addBullets();

};

#endif