#include "Player.h"
#include <iostream>
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "CollisionComponent.h"
#include "Tile.h" 
#include "RayComponent.h"
#include "World.h"
Player::Player(const std::string& ID,Game * game)
	:Actor(ID,game),
	xsp(0.0f),ysp(0.0f),gsp(0.0f),angle(0),
	acc(0.046875),dec(0.5),frc(acc),top(6),
	air(0.09375), jmp(6.5), knxjmp(6), grv(0.21875),
	facingDirection(1),movingDirection(1),
	leftPressed(false),rightPressed(false),isOnGround(false)
{

}

void Player::init()
{
	this->setPosition(Vector2(512.0f, 384.0f));
	this->setScale(2);
	sprite = new AnimSpriteComponent(this,101);
	sprite->addAnimation("run", "Assets/playerAnimSheets/run0.png", 0, 0, 50, 37, 9, 6);
	sprite->addAnimation("jump", "Assets/playerAnimSheets/jump.png", 0, 0, 50, 37, 7, 4);
	sprite->addAnimation("fall", "Assets/playerAnimSheets/fall.png", 0, 0, 50, 37, 7, 2);
	sprite->addAnimation("idle", "Assets/playerAnimSheets/idle0.png", 0, 0, 50, 37, 5, 3);
	sprite->setAnimation("idle", -1);

	collider = new CollisionComponent(this);
	collider->setRectLocal(0,5,45, 65);
	updateObjectBounds();
	
	RayComponent* ray = new RayComponent(this, RayComponent::BOTTOM);
	ray = new RayComponent(this, RayComponent::RIGHT);
	ray = new RayComponent(this, RayComponent::LEFT);

}
void Player::updateActor(float deltaTime)
{
	Vector2 pos = this->getPosition();
	updateObjectBounds();

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
	

	if (abs(gsp) > top)
		gsp = top*movingDirection;

	if (isOnGround)
	{
		xsp = gsp * cos(angle * M_PI / 180);
		ysp = gsp * (-sin(angle * M_PI / 180));
	}
	else
	{
		xsp = gsp * cos(angle * M_PI / 180);
		ysp += grv;
		if (ysp > 16)
		{
			ysp = 16;
		}
		pos.y += ysp;
	}
	pos.x += xsp;
	
	if (pos.x > 149*16)
		pos.x = 149*16;
	else if (pos.x < 16)
		pos.x = 16;

	this->setPosition(pos);
	this->setRotation(angle);

	if (!isOnGround && ysp > 0)
	{
		if (this->sprite->currentAnimID != "fall")
		{
			this->sprite->setAnimation("fall", -1);
		}
	}
	isOnGround = false;

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
void Player::currentAnimFrame(const std::string & animName, int frame)
{
	
}

void Player::actorInput(const uint8_t * keystate)
{
	leftPressed = false;
	rightPressed = false;
	if (keystate[SDL_SCANCODE_LEFT])
	{
		leftPressed = true;
		movingDirection = -1;
		gsp += acc*movingDirection;
		if (gsp > 0)
		{
			gsp += dec* movingDirection;
		}
		if (gsp < 0)
		{
			facingDirection = -1;
			this->flipStateX = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		}

		if (this->sprite->currentAnimID != "run")
		{
			this->sprite->setAnimation("run", -1);
		}
	}
	else if(keystate[SDL_SCANCODE_RIGHT])
	{
		rightPressed = true;

		movingDirection = 1;
		gsp += acc*movingDirection;
		if (gsp < 0)
		{
			gsp += dec*movingDirection;
		}
		if (gsp > 0)
		{
			facingDirection = 1;
			this->flipStateX = SDL_RendererFlip::SDL_FLIP_NONE;
		}

		if (this->sprite->currentAnimID != "run")
		{
			this->sprite->setAnimation("run", -1);
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
		else
		{
			if (this->sprite->currentAnimID != "run")
			{
				this->sprite->setAnimation("run", -1);
			}

			movingDirection = gsp / abs(gsp);
		}
		
	}

	if (keystate[SDL_SCANCODE_SPACE])
	{
		if (isOnGround)
		{
			ysp = -jmp;
			isOnGround = false;
		}
		
	}
	//animation speed according to the acceleration
	sprite->setFrameRate(sprite->getOriginalFrameRate()+abs(gsp));
	
}

void Player::rayCastResult(short unsigned int type,Vector2 position)
{
	switch (type)
	{
	case RayComponent::RIGHT:
		if (movingDirection > 0)
		{
			gsp = 0;
			Vector2 pos = getPosition();
			pos.x = floor((position.x + World::camera.x) / 16) * 16 - 45 / 2;
			setPosition(pos);
		}
		break;
	case RayComponent::LEFT:
		if (movingDirection < 0)
		{
			gsp = 0;
			Vector2 pos = getPosition();
			pos.x = floor((position.x + World::camera.x) / 16) * 16 + 16 + 45/2;
			setPosition(pos);
		}
		break;
	default:
		if (ysp < 0)
			return;
		if (!isOnGround)
		{
			isOnGround = true;
			if (ysp > 0)
			{
				ysp = 0;
				Vector2 pos = getPosition();
				pos.y = floor((position.y +World::camera.y) / 16) * 16 - 36;
				setPosition(pos);
			}
		}
	}
	
}
