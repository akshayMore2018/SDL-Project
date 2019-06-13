#include "Tile.h"

Tile::Tile(const std::string & ID):ID(ID),width(16),height(16)
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