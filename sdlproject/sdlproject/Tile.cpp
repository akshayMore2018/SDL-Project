#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "CollisionComponent.h"

Tile::Tile(Game * game)
	:Actor(game)
{
	getGame()->addTile(this);
}

Tile::~Tile()
{
	getGame()->removeTile(this);
}

void Tile::init()
{
	this->setScale(2);
	collider = new CollisionComponent(this);
	collider->setRectLocal(0, 0, 64, 32);
	updateObjectBounds();

	SpriteComponent* sprite = new SpriteComponent(this);
	sprite->setTexture(this->getGame()->getTexture("Assets/metaTiles.png"));
}

void Tile::updateActor(float deltaTime)
{
	updateObjectBounds();
}
