#pragma once
#include "Actor.h"

class Player :public Actor
{
public:
	Player(const std::string&  ID,class Game* game);
	
	void init();

	void updateActor(float deltaTime);
	void onAnimCompleteEvent(const std::string & animName);
	void actorInput(const uint8_t * keystate);
	void rayCastResult(Vector2 position);

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

	const float air; 
	const float jmp; 
	const float knxjmp;
	const float	grv; 

	bool leftPressed;
	bool rightPressed;
	int facingDirection;
	int movingDirection;
	bool isOnGround;
};