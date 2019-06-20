#include "CollisionComponent.h"
#include "Actor.h"
#include "GameView.h"
#include "World.h"
#include <iostream>
CollisionComponent::CollisionComponent(Actor * owner, int updateOrder)
:Component(owner,updateOrder), collisionRect{0,0,0,0},left(0),right(0),top(0),bottom(0)
{
	this->m_Owner->getView()->addCollider(this);
}

CollisionComponent::~CollisionComponent()
{
	this->m_Owner->getView()->removeCollider(this);
}

void CollisionComponent::draw(SDL_Renderer * renderer)
{
	SDL_RenderDrawRect(renderer, &this->collisionRect);
}

void CollisionComponent::update(float deltaTime)
{
	collisionRect.x = static_cast<int>(this->m_Owner->getPosition().x-collisionRect.w/2 + localX - World::camera.x);
	collisionRect.y = static_cast<int>(this->m_Owner->getPosition().y-collisionRect.h/2 + localY - World::camera.y);
	updateObjectBounds();
}

void CollisionComponent::updateObjectBounds()
{
	left = collisionRect.x;
	right = collisionRect.x + collisionRect.w;
	top = collisionRect.y;
	bottom = collisionRect.y + collisionRect.h;
}

void CollisionComponent::setRectLocal(float x, float y,float width, float height)
{
	localX = x;
	localY = y;
	collisionRect.w = static_cast<int>(width);
	collisionRect.h = static_cast<int>(height);
}
