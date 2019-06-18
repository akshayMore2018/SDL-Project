#pragma once
#include <iostream>
#include "Math.h"
#include "SDL.h"
#include "Actor.h"
class Tile : public Actor 
{
public:

	Tile(const std::string& ID, class Game* game);
	void init(const short unsigned int type, int tileSetID,int x, int y, int w, int h);

	const Vector2& getPosition()const { return position; }
	const Vector2& getImgSrc()const { return imgSrc; }
	const int getWidth()const { return width; }
	const int getHeight()const { return height; }

	const int getTileID()const { return ID; }
	short unsigned int type;
private:
	
	int ID;
	Vector2 position;
	int width, height;
	Vector2 imgSrc;
};