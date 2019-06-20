#include "Actor.h"
#include "GameView.h"
#include "Component.h"
#include "CollisionComponent.h"
#include <iostream>
Actor::Actor(const std::string& ID, class GameView* view)
	:ID(ID),m_State(EActive),m_Position(Vector2(0,0)),m_Scale(1.0f),m_Rotation(0.0f)
	,m_View(view), flipStateX(SDL_RendererFlip::SDL_FLIP_NONE)
{
	this->m_View->addActor(this);
}

Actor::~Actor()
{
	this->m_View->removeActor(this);

	while (!m_Components.empty())
	{
		delete m_Components.back();
	}
}

void Actor::update(float deltaTime)
{
	if (m_State == EActive)
	{
		this->updateActor(deltaTime);
		this->updateComponent(deltaTime);
	}
}

void Actor::updateComponent(float deltaTime)
{
	for (auto comp : this->m_Components)
	{
		comp->update(deltaTime);

	}
}

void Actor::updateActor(float deltaTime)
{
	updateObjectBounds();
}

void Actor::onAnimCompleteEvent(const std::string & animName)
{
}

void Actor::currentAnimFrame(const std::string & animName,int frame)
{
}

void Actor::actorInput(const uint8_t * keystate)
{
}

void Actor::processInput(const uint8_t * keystate)
{
	if (this->m_State == EActive)
	{
		for (auto comp : this->m_Components)
		{
			comp->processInput(keystate);
		}
		actorInput(keystate);

	}
}

void Actor::addComponent(Component * component)
{
	int myOrder = component->getUpdateOrder();
	auto iter = m_Components.begin();
	for (;
		iter != m_Components.end();
		++iter)
	{
		if (myOrder < (*iter)->getUpdateOrder())
		{
			break;
		}
	}
	m_Components.insert(iter, component);
}

void Actor::removeComponent(Component * component)
{
	auto iter = std::find(m_Components.begin(), m_Components.end(), component);
	if (iter != m_Components.end())
	{
		m_Components.erase(iter);
	}
}
void Actor::updateObjectBounds()
{
	if (collider)
	{
		left = collider->getLeft();
		right = collider->getRight();
		top = collider->getTop();
		bottom = collider->getBottom();
	}
	
}

void Actor::rayCastResult(short unsigned int type,Vector2 position)
{

}
