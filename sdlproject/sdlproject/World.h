#pragma once
#include "Game.h"
#include "Actor.h"


class World : public Actor
{
public:
	World(const std::string& ID, class Game* game);
	~World();
	const class Tile* getTile(int x, int y)const;
	void init();
	void setDimension(int w, int h);
	int getXTiles()const { return w; }
	int getYTiles()const { return h; }
	void addTile(int x, int y, class Tile* tile);
private:
	
	int w;
	int h;
	std::vector<std::vector<class Tile*> > map;
};