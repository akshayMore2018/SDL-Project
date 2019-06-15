#include "World.h"
#include "Math.h"
#include "Tile.h"
#include "TileMapComponent.h"

SDL_Rect World::camera = { 0,0,1024,768 };
const int World::mapWidth = 150 * 16;
const int World::mapHeight = 48 * 16;


World::World(const std::string& ID, class Game* game):
Actor(ID,game)
{

}

World::~World()
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			delete getTile(j, i);
		}
	}
	map.clear();
}

void World::updateActor(float deltaTime)
{
	camera.x = mPlayer->getPosition().x - camera.w / 2;
	camera.y = mPlayer->getPosition().y - camera.h / 2;

	if (camera.x < 0)camera.x = 0;
	if (camera.y < 0)camera.y = 0;



	if ((camera.x + camera.w) > mapWidth)camera.x = mapWidth - camera.w;
	if ((camera.y + camera.h) > mapHeight)camera.y = mapHeight - camera.h;
}

void World::init()
{
	this->w = mapWidth / TileMapComponent::tileWidth;
	this->h = mapHeight / TileMapComponent::tileHeight;
	map.resize(w);
	for (int i = 0; i < w; i++)
	{
		map.at(i).resize(h, 0);
	}


	TileMapComponent* tileMap = new TileMapComponent(this);
	tileMap->loadMap("Assets/map/map.csv");
}

const Tile * World::getTile(int x, int y)const
{
	return map[x][y];
}



void World::addTile(int x, int y, Tile * tile)
{
	map[x][y] = tile;
}

void World::setPlayer(Actor * player)
{
	this->mPlayer = player;
}
