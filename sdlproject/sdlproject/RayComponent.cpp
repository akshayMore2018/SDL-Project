#include "RayComponent.h"
#include "Actor.h"
#include "Game.h"
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
	this->points = Math::Bresenham(m_Owner->getLeft(), m_Owner->getBottom(), m_Owner->getLeft(), m_Owner->getBottom() + 50);
}
