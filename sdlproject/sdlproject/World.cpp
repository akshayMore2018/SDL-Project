#include "World.h"
#include "Math.h"
#include "Tile.h"
World::World(int w, int h,Game * game):w(w),h(h),mGame(game)
{

}

void World::init()
{
	setDimension(w, h);

	for (int i = 30; i < h; i++)
	{
		for (int j = 0; j < w ; j++)
		{
			Tile* tile = new Tile("Tile", this->mGame);
			tile->setPosition(Vector2((j * 16 + 8), (i * 16 + 8)));
			tile->init();
			addTile(j, i, tile);
		}
	}

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
	map.resize(w);

	for (int i = 0; i < w; i++)	
	{
			map.at(i).resize(h, 0);
	}

}
