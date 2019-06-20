#pragma once
#include "Actor.h"

class Player :public Actor
{
public:
	friend class BGSpriteComponent;
	Player(const std::string& ID,class View* view);
	
	void init();

	void updateActor(float deltaTime);
	void onAnimCompleteEvent(const std::string & animName);
	void currentAnimFrame(const std::string & animName,int frame);
	void actorInput(const uint8_t * keystate);
	void rayCastResult(short unsigned int type,Vector2 position);

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