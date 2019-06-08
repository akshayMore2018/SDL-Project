#include "Player.h"
#include <iostream>
#include "Game.h"
#include "AnimSpriteComponent.h"
Player::Player(Game * game)
	:Actor(game), mSpeed(0), mRunning(false), mAttacking(false)
{

}

void Player::init()
{
	this->setPosition(Vector2(512.0f, 384.0f));
	this->setScale(3);
	sprite = new AnimSpriteComponent(this);
	sprite->addAnimation("run", "Assets/playerAnimSheets/run0.png", 0, 0, 50, 37, 9, 6);
	sprite->addAnimation("groundAttack01", "Assets/playerAnimSheets/groundAttack01.png", 0, 0, 50, 37, 7, 5);
	sprite->addAnimation("idle", "Assets/playerAnimSheets/idle0.png", 0, 0, 50, 37, 5, 3);
	sprite->setAnimation("idle", -1);
}

void Player::updateActor(float deltaTime)
{
	Vector2 pos = this->getPosition();

	pos.x += this->mSpeed * deltaTime;

	this->setPosition(pos);

	
	
}

void Player::onAnimCompleteEvent(const std::string & animName)
{
	if (animName == "idle")
	{
		sprite->setAnimation("groundAttack01", 1);
	}
	else if (animName == "groundAttack01")
	{
		sprite->setAnimation("idle", -1);
		this->mAttacking = false;
	}
	else if (animName == "run")
	{
		sprite->setAnimation("idle", -1);
	}
	
}

void Player::actorInput(const uint8_t * keystate)
{
	this->mSpeed = 0;
	this->mRunning = false;
	if (this->mAttacking)
		return;
	if (keystate[SDL_SCANCODE_LEFT])
	{
		this->mSpeed = -100;
		this->mRunning = true;
		this->flipStateX = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		
	}
	else if(keystate[SDL_SCANCODE_RIGHT])
	{
		this->mSpeed = 100;
		this->mRunning = true;
		this->flipStateX = SDL_RendererFlip::SDL_FLIP_NONE;
	}
	else if(keystate[SDL_SCANCODE_SPACE])
	{
		this->mAttacking = true;
	}

	if (this->mRunning)
	{
		if (this->sprite->currentAnimID != "run")
		{
			this->sprite->setAnimation("run", -1);
		}
	}
	else if (this->mAttacking)
	{
		if (this->sprite->currentAnimID != "groundAttack01")
		{
			this->sprite->setAnimation("groundAttack01", 1);
		}
	}
	else
	{
		if (this->sprite->currentAnimID != "idle")
		{
			this->sprite->setAnimation("idle", -1);
		}
	}
}
