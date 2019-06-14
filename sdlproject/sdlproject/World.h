#pragma once
#include "Game.h"
#include "Actor.h"


class World : public Actor
{
public:
	World(const std::string& ID, class Game* game);
	~World();
	void updateActor(float deltaTime);
	const class Tile* getTile(int x, int y)const;
	void init();
	int getXTiles()const { return w; }
	int getYTiles()const { return h; }
	void addTile(int x, int y, class Tile* tile);
	void setPlayer(Actor* player);
	static SDL_Rect camera;
	static const int  mapWidth;
	static const int  mapHeight;
private:
	
	int w;
	int h;
	std::vector<std::vector<class Tile*> > map;
	Actor* mPlayer;
	
};