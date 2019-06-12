#pragma once
#include "Actor.h"
class Tile : public Actor
{
public:
	Tile(const std::string& ID,class Game* game);
	void init();
	void updateActor(float deltaTime);
};