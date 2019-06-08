#include "Actor.h"
#include "Game.h"
#include "Component.h"
Actor::Actor(Game * game)
	:m_State(EActive),m_Position(Vector2(0,0)),m_Scale(1.0f),m_Rotation(0.0f)
	,m_Game(game), flipStateX(SDL_RendererFlip::SDL_FLIP_NONE)
{
	this->m_Game->addActor(this);
}

Actor::~Actor()
{
	this->m_Game->removeActor(this);

	while (!m_Components.empty())
	{
		delete m_Components.back();
	}
}

void Actor::update(float deltaTime)
{
	if (m_State == EActive)
	{
		this->updateComponent(deltaTime);
		this->updateActor(deltaTime);
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
}

void Actor::onAnimCompleteEvent(const std::string & animName)
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
