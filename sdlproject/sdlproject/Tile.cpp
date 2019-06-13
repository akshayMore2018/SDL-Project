#include "Tile.h"

Tile::Tile(const std::string & ID):ID(ID),width(16),height(16)
{

}

void Tile::init()
{
		
}

void Tile::updateTile(float deltaTime)
{
	
}

void Tile::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}
