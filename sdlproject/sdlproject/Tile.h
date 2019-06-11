#pragma once
#include "Actor.h"
class Tile : public Actor
{
public:
	Tile(class Game* game);
	~Tile();
	void init();
	void updateActor(float deltaTime);
};