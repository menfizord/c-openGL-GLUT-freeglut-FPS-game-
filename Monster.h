
#ifndef Monster_H
#define Monster_H
#include "stdafx.h"

class Monster {
private:
	GLuint obj, tex;
	float t=0;
	float playerPos;
	float actualPos;
	float endingPos;
	float startingPos;
	void calculateActualPos(); //movement of monster
	int change = 0;
	bool dead = false;
	bool stopMoving = false;
	float stopPosition;
	float flyOut=0.0f;
	bool timeToDelete = false;

public:
	Monster(GLuint, GLuint,float);
	void getPlayerPos(float);
	void draw();
	int checkCol(std::vector<Bullet*>);
	int checkPlayerCol();
	float getDeadPos();
};



#endif 