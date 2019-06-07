#include "Component.h"
#include "Actor.h"
Component::Component(Actor * owner, int updateOrder)
	:m_Owner(owner),m_UpdateOrder(updateOrder)
{
	this->m_Owner->addComponent(this);
}

Component::~Component()
{
	this->m_Owner->removeComponent(this);
}

void Component::update(float deltaTime)
{
}


