#pragma once
#include "Game.h"


class World
{
public:
	World(int w, int h,class Game* game);
	class Tile* GetTile(int x, int y);
	void init();

private:
	void addTile(int x, int y, class Tile* tile);

	class Game* mGame;
	int w;
	int h;
	std::vector<std::vector<class Tile*> > map;
};