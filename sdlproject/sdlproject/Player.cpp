#include "Player.h"
#include <iostream>
#include "Game.h"
#include "AnimSpriteComponent.h"
Player::Player(Game * game)
	:Actor(game), mSpeed(0)
{

}

void Player::init()
{
	this->setPosition(Vector2(512.0f, 384.0f));
	this->setScale(3);
	sprite = new AnimSpriteComponent(this);
	sprite->addAnimation("run", "Assets/playerAnimSheets/run0.png", 0, 0, 50, 37, 3, 6);
	sprite->addAnimation("groundAttack01", "Assets/playerAnimSheets/groundAttack01.png", 0, 0, 50, 37, 7, 5);
	sprite->addAnimation("idle", "Assets/playerAnimSheets/idle0.png", 0, 0, 50, 37, 5, 3);
	sprite->setAnimation("idle", 3);
}

void Player::updateActor(float deltaTime)
{
	
	
}

void Player::onAnimCompleteEvent(const std::string & animName)
{
	if (animName == "idle")
	{
		sprite->setAnimation("groundAttack01", 1);
	}
	else if (animName == "groundAttack01")
	{
		sprite->setAnimation("idle", 3);
	}
	
}
