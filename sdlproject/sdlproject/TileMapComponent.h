#pragma once
#include "SpriteComponent.h"
#include <vector>

class TileMapComponent :public SpriteComponent
{
public:
	TileMapComponent(class Actor* owner, int draworder = 100);

	void loadMap(const std::string& mapFile, const std::string& tileSet);
	void draw(SDL_Renderer* renderer);

private:
	std::vector<class Tile*> tiles;
	int horTileCount;
	int verTileCount;
	const int tileWidth;
	const int tileHeight;
};

class Tile
{
public:
	Tile(int ID, int dstR , int dstC,int tilesX)
		:ID(ID),dst{ dstR * 16,dstC * 16, 16, 16}, src{ (ID%tilesX) * 16 ,(ID/tilesX) * 16, 16, 16 }
	{}
	int ID;
	SDL_Rect src;
	SDL_Rect dst;
};