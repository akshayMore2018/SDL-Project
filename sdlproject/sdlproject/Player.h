#pragma once
#include "Actor.h"

class Player :public Actor
{
public:
	Player(class Game* game);
	
	void init();

	void updateActor(float deltaTime);
	void onAnimCompleteEvent(const std::string & animName);
	void actorInput(const uint8_t * keystate);

private:
	class AnimSpriteComponent* sprite;
	
	float xsp;
	float ysp;
	float gsp;
	float angle;
	const float acc;
	const float dec;
	const float frc;
	const float top;

	bool leftPressed;
	bool rightPressed;
	int facingDirection;
	int movingDirection;
};