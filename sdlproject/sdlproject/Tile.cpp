#include "Tile.h"
#include "TileMapComponent.h"
#include "World.h"
#include "GameView.h"

Tile::Tile(const std::string & ID, GameView* view)
:Actor(ID,view)
{

}

void Tile::init(const short unsigned int type, int tileSetID,int x, int y , int w, int h)
{
	this->type = type;
	this->ID = tileSetID;
	this->position.x = x*w;
	this->position.y = y*h;
	this->width = w;
	this->height = h;

	int drawOrder = 100;

	switch (type)
	{
	case World::BACKGROUND:
		drawOrder = 40;
		break;
	case World::SOLID:
		drawOrder = 100;
		break;
	case World::FOREGROUND:
		drawOrder = 110;
		break;
	}

	TileMapComponent* comp = new TileMapComponent(this,drawOrder);
	comp->setTexture(getView()->getTexture("Assets/map/tileset.png"));
	int xTileImages = comp->getTextureWidth() / World::tileWidth;
	this->imgSrc.x = (ID % xTileImages) * width;
	this->imgSrc.y = (ID / xTileImages) * height;

}

