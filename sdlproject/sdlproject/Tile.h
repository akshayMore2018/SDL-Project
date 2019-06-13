#pragma once
#include <iostream>
#include "Math.h"
#include "SDL.h"
class Tile 
{
public:
	Tile(const std::string& type, int tileSetID);
	void init(int x, int y, int w, int h);
	void updateTile(float deltaTime);

	void setImgSrcCoord(int x, int y);

	const Vector2& getPosition()const { return position; }
	const Vector2& getImgSrc()const { return imgSrc; }
	const int getWidth()const { return width; }
	const int getHeight()const { return height; }

	const int getTileID()const { return ID; }

private:
	std::string type;
	int ID;
	Vector2 position;
	int width, height;
	Vector2 imgSrc;
};