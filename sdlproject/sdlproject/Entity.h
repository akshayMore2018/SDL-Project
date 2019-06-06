#pragma once
#include <unordered_set>
class Entity
{
public:
	void addComponent(class Component* component);
	void removeComponent(class Component* component);

private:
	std::unordered_set<Component*> m_Components;
};