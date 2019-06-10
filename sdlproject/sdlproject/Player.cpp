#include "Player.h"
#include <iostream>
#include "Game.h"
#include "AnimSpriteComponent.h"
Player::Player(Game * game)
	:Actor(game),
	xsp(0.0f),ysp(0.0f),gsp(0.0f),angle(0),
	acc(0.046875),dec(0.5),frc(acc),top(6),
	facingDirection(1),movingDirection(1),
	leftPressed(false),rightPressed(false)
{

}

void Player::init()
{
	this->setPosition(Vector2(512.0f, 384.0f));
	this->setScale(2);
	sprite = new AnimSpriteComponent(this);
	sprite->addAnimation("run", "Assets/playerAnimSheets/run0.png", 0, 0, 50, 37, 9, 6);
	sprite->addAnimation("groundAttack01", "Assets/playerAnimSheets/groundAttack01.png", 0, 0, 50, 37, 7, 5);
	sprite->addAnimation("idle", "Assets/playerAnimSheets/idle0.png", 0, 0, 50, 37, 5, 3);
	sprite->setAnimation("idle", -1);
}

void Player::updateActor(float deltaTime)
{
	if (!(leftPressed || rightPressed))
	{
		
		if (abs(gsp) > frc)
		{
			gsp += frc * -movingDirection;
		}
		else
		{
			gsp = 0.0f;
		}
	}
	
	Vector2 pos = this->getPosition();

	if (gsp > top)
		gsp = top;

	xsp = gsp * cos(angle * M_PI/180);
	ysp = gsp * (-sin(angle * M_PI / 180));

	pos.x += xsp;
	pos.y += ysp;


	if (pos.x > 1030)
		pos.x = -10;

	this->setPosition(pos);
	this->setRotation(angle);
}

void Player::onAnimCompleteEvent(const std::string & animName)
{
	if (animName == "idle")
	{
		sprite->setAnimation("groundAttack01", 1);
	}
	else if (animName == "run")
	{
		sprite->setAnimation("idle", -1);
	}
	
}

void Player::actorInput(const uint8_t * keystate)
{
	leftPressed = false;
	rightPressed = false;
	if (keystate[SDL_SCANCODE_LEFT])
	{
		movingDirection = -1;
		gsp += acc*movingDirection;
		leftPressed = true;
		if (gsp > 0)
		{
			gsp += dec* movingDirection;
		}

		if (this->sprite->currentAnimID != "run")
		{
			this->sprite->setAnimation("run", -1);
		}
		if (gsp < 0)
		{
			facingDirection = -1;
			this->flipStateX = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}
		
		
	}
	else if(keystate[SDL_SCANCODE_RIGHT])
	{
		movingDirection = 1;
		gsp += acc*movingDirection;
		rightPressed = true;
		if (gsp < 0)
		{
			gsp += dec*movingDirection;
		}
		if (this->sprite->currentAnimID != "run")
		{
			this->sprite->setAnimation("run", -1);
		}
		if (gsp > 0)
		{
			facingDirection = 1;
			this->flipStateX = SDL_RendererFlip::SDL_FLIP_NONE;
		}
	}
	else
	{
		if (gsp == 0)
		{
			if (this->sprite->currentAnimID != "idle")
			{
				this->sprite->setAnimation("idle", -1);
			}
		}
	}
	//animation speed according to the acceleration
	sprite->setFrameRate(sprite->getOriginalFrameRate()+abs(gsp));
	
}
