#pragma once
#include "Game.h"
#include "Actor.h"


class World : public Actor
{
public:
	World(const std::string& ID, class Game* game);
	~World();
	void updateActor(float deltaTime);
	void init();
	void setPlayer(Actor* player);
	static SDL_Rect camera;
	class TileMapComponent* onemap;
	
private:
	Actor* mPlayer;
};