#include "World.h"
#include "TileMapComponent.h"

World::World(Game * game)
	:Actor(game), map(nullptr)
{
}

void World::init()
{
	map = new TileMapComponent(this);
	map->loadMap("Assets/map/test.csv", "Assets/map/tileset.png");

}
