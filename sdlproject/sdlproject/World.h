#pragma once
#include "Actor.h"


class World :public Actor
{
public:
	World(class Game* game);
	void init();
private:
	class TileMapComponent* map;
};