#include "Tile.h"


Tile::Tile(const short unsigned int type ,int tileSetID):type(type),ID(tileSetID)
{
	
}

void Tile::init(int x, int y , int w, int h)
{
	this->position.x = x*w;
	this->position.y = y*h;
	this->width = w;
	this->height = h;
}

void Tile::updateTile(float deltaTime)
{
	
}

void Tile::setImgSrcCoord(int x, int y)
{
	this->imgSrc.x = x * width;
	this->imgSrc.y = y * height;
}
