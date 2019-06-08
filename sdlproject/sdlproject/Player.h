#pragma once
#include "Actor.h"

class Player :public Actor
{
public:
	Player(class Game* game);
	
	void init();

	void updateActor(float deltaTime);
	void onAnimCompleteEvent(const std::string & animName);
private:
	float mSpeed;
	class AnimSpriteComponent* sprite;
};