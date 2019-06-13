#include "RayComponent.h"
#include "Actor.h"
#include "Game.h"
#include "World.h"
#include <iostream>
RayComponent::RayComponent(Actor * owner, int updateOrder)
	:Component(owner, updateOrder)
{
	this->m_Owner->getGame()->addRay(this);
}

RayComponent::~RayComponent()
{
	this->m_Owner->getGame()->removeRay(this);
}

void RayComponent::draw(SDL_Renderer * renderer)
{
	for (auto pt : points)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer, pt.x, pt.y);
	}
}

void RayComponent::update(float deltaTime)
{
	this->points = Math::Bresenham(m_Owner->getLeft()+20, m_Owner->getBottom(), m_Owner->getLeft()+20, m_Owner->getBottom() + 25);
	int rayPointIndex = 0;
	if(points.size()>0)
	rayPointIndex = points.size()-1;
	while (true) 
	{
		rayPoint = points[rayPointIndex];
		if (!canPointBeTravelled(rayPoint.x, rayPoint.y)) {
			position = rayPoint;
			this->m_Owner->rayCastResult(position);
			break;
		}
		if (points[0] != position) {
			rayPointIndex--;
			if (rayPointIndex < 0) break;
		}
		else {
			rayPointIndex++;
			if (rayPointIndex >= points.size()) break;
		}
	}
}

const Tile * RayComponent::getTile() const
{
	return nullptr;
}

bool RayComponent::canPointBeTravelled(int x, int y)
{
	int r = floor(x / 16);
	int c = floor(y / 16);
	
	if (r < 0)return true;
	if (r > 63)return true;
	if (c < 0)return true;
	if (c > 47)return true;


	if ((this->m_Owner->getGame()->getWorld()->getTile(r, c))==nullptr)
	{
		return true;
	}

	return false;
}
