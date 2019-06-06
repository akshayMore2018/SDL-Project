#pragma once
#include "SDL.h"
#include <vector>
struct Vector2
{
	float x;
	float y;
};
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void update(float deltaTime);
	void updateComponent(float deltaTime);
	virtual void updateActor(float deltaTime);

	void addComponent(class Component* component);
	void removeComponent(class Component* component);
	inline State getState()const;

private:
	State m_State;
	Vector2 m_Position;
	float m_Scale;
	float m_Rotation;
	std::vector<class Component*> m_Components;
	class Game* m_Game;
};
inline Actor::State Actor::getState() const
{
	return this->m_State;
}