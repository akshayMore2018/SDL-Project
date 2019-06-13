#include "World.h"
#include "Math.h"
#include "Tile.h"
#include "TileMapComponent.h"
World::World(const std::string& ID, class Game* game):
Actor(ID,game)
{

}

void World::init()
{
	TileMapComponent* map = new TileMapComponent(this);
	map->loadMap();

}

const Tile * World::GetTile(int x, int y)const
{
	return map[x][y];
}



void World::addTile(int x, int y, Tile * tile)
{
	map[x][y] = tile;
}

void World::setDimension(int w, int h)
{
	this->w = w;
	this->h = h;
	map.resize(w);

	for (int i = 0; i < w; i++)	
	{
			map.at(i).resize(h, 0);
	}

}
