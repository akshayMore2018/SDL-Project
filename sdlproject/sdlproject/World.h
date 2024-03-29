#pragma once
#include "Game.h"
#include "Actor.h"
#include <map>

class World : public Actor
{
public:
	enum LAYER
	{
		BACKGROUND,
		MIDDLEGROUND,
		FOREGROUND,
		SOLID
	};
	World(const std::string& ID, class GameView* view);
	~World();
	void updateActor(float deltaTime);
	void init();
	void setPlayer(Actor* player);
	static SDL_Rect camera;
	void loadMap(const std::string& file);

	const class Tile* getTile(int x, int y);

	static  int tileWidth;
	static  int tileHeight;
	static  int xTiles;
	static  int yTiles;
	static  int mapWidth;
	static  int mapHeight;
	
private:
	Actor* mPlayer;
	std::map<std::string,std::vector<std::vector<class Tile*>>> map;
};