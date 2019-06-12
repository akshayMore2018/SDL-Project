#pragma once
#include "Game.h"


class World
{
public:
	World(int w, int h,class Game* game);
	const class Tile* GetTile(int x, int y)const;
	void init();

private:
	void addTile(int x, int y, class Tile* tile);
	void setDimension(int w, int h);
	class Game* mGame;
	int w;
	int h;
	std::vector<std::vector<class Tile*> > map;
};