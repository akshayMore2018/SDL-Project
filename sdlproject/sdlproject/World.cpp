#include "World.h"
#include "Math.h"
#include "Tile.h"
#include "TileMapComponent.h"


SDL_Rect World::camera = { 0,0,1024,768 };

World::World(const std::string& ID, class Game* game):
Actor(ID,game)
{

}

World::~World()
{
	
}

void World::updateActor(float deltaTime)
{
	camera.x = mPlayer->getPosition().x - camera.w / 2;
	camera.y = mPlayer->getPosition().y - camera.h / 2;

	if (camera.x < 0)camera.x = 0;
	if (camera.y < 0)camera.y = 0;

	if ((camera.x + camera.w) > TileMapComponent::mapWidth)camera.x = TileMapComponent::mapWidth - camera.w;
	if ((camera.y + camera.h) > TileMapComponent::mapHeight)camera.y = TileMapComponent::mapHeight - camera.h;
}

void World::init()
{
	onemap = new TileMapComponent(this);
	onemap->loadMap("Assets/map/map.csv");

}
void World::setPlayer(Actor * player)
{
	this->mPlayer = player;
}

