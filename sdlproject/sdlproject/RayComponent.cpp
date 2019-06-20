#include "RayComponent.h"
#include "Actor.h"
#include "View.h"
#include "World.h"
#include "Tile.h"
#include <iostream>
#include "TileMapComponent.h"
RayComponent::RayComponent(Actor * owner, RAY type, int updateOrder)
	:Component(owner, updateOrder)
{
	this->m_Owner->getView()->addRay(this);
	this->rayType = type;
}

RayComponent::~RayComponent()
{
	this->m_Owner->getView()->removeRay(this);
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
	switch (rayType)
	{
	case LEFT:
		this->points = Math::Bresenham(m_Owner->getLeft(), m_Owner->getBottom() - 10, (m_Owner->getLeft() - 2), m_Owner->getBottom() - 10);
		break;
	case RIGHT:
		this->points = Math::Bresenham(m_Owner->getRight(), m_Owner->getBottom() - 10, (m_Owner->getRight() + 2), m_Owner->getBottom() - 10);
		break;
	default:
		this->points = Math::Bresenham((m_Owner->getLeft() + 20), m_Owner->getBottom(), (m_Owner->getLeft() + 20), m_Owner->getBottom() + 7);
	}
	
	int rayPointIndex = 0;
	if(points.size()>0)
	rayPointIndex = points.size()-1;
	while (true) 
	{
		rayPoint = points[rayPointIndex];
		if (!canPointBeTravelled(rayPoint.x, rayPoint.y)) {
			position = rayPoint;
			this->m_Owner->rayCastResult(rayType,position);
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

bool RayComponent::canPointBeTravelled(int x, int y)
{
	int r = floor((x + World::camera.x) / World::tileWidth);
	int c = floor((y + World::camera.y) / World::tileHeight);
	
	if (r < 0)return true;
	if (r > World::xTiles - 1)return true;
	if (c < 0)return true;
	if (c > World::yTiles - 1)return true;

	if ((this->m_Owner->getView()->getWorld()->getTile(r, c))==nullptr)
	{
		return true;
	}
	return false;
}
