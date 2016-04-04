#ifndef Map_H
#define MAP_H
#include <vector>
#include "stdafx.h"
#include "Barriere.h"
#include "Car.h"
class Map {
public:
	Map();
	~Map();
	void makeQuads();
	void loadTexts();
	void drawQuads();
	void loadObjects();
	void drawObjts();
	void LoadTextsToObj();
	void drawLamps();
	void drawSky(); //na Podstawie kodu Pana Bazyluka 
private:
	std::vector<GLuint> texts; //vector of bitmaps
	std::vector<Barriere*> Barriers; // vector of static objects 
	std::vector<Car*> Cars;
	std::vector<GLuint> textsToObj;
	std::vector<std::vector<Quad*>> Quads; //vector of walls floor etc
	GLuint skyTex, lampTex,backBuildingTex;
};



#endif // !Map_H