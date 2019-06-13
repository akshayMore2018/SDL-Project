#pragma once
#include <iostream>
#include "Math.h"
class Tile 
{
public:
	Tile(const std::string& ID);
	void init(int x, int y, int w, int h);
	void updateTile(float deltaTime);
	const Vector2& getPosition()const { return position; }
	const int getWidth()const { return width; }
	const int getHeight()const { return height; }
private:
	std::string ID;
	Vector2 position;
	int width, height;
};