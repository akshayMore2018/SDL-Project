#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(const std::string& ID,Game * game)
	:Actor(ID,game)
{
}
void Tile::init()
{
	collider = new CollisionComponent(this);
	collider->setRectLocal(0, 0, 16, 16);
	updateObjectBounds();

	SpriteComponent* sprite = new SpriteComponent(this);
	int i = rand() % 6;
	if (i > 3)
	{
		sprite->setTexture(this->getGame()->getTexture("Assets/map/metaTile.png"));
	}
	else
	{
		sprite->setTexture(this->getGame()->getTexture("Assets/map/metaTile2.png"));
	}
		
}

void Tile::updateActor(float deltaTime)
{
	updateObjectBounds();
}
