#pragma once
#include "SpriteComponent.h"
#include <vector>

class TileMapComponent :public SpriteComponent
{
	friend class Tile;
public:
	TileMapComponent(class Actor* owner, int draworder = 100);
	~TileMapComponent();
	void loadMap(const std::string& mapFile, const std::string& tileSet);
	void draw(SDL_Renderer* renderer);

private:
	std::vector<class Tile*> tiles;
	int horTileCount;
	int verTileCount;
	const int tileWidth;
	const int tileHeight;
	friend class Tile;
	
};

class Tile
{
public:
	Tile(int ID, int dstR , int dstC,TileMapComponent* map)
		:ID(ID),
		dst{ dstR * map->tileWidth,dstC * map->tileHeight, map->tileWidth, map->tileHeight },
		src{ (ID%map->horTileCount) * map->tileWidth ,(ID/map->horTileCount) * map->tileHeight, map->tileWidth, map->tileHeight }
	{
		
	}
	int ID;
	SDL_Rect src;
	SDL_Rect dst;
};