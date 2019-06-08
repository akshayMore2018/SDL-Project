#pragma once
#include "SDL.h"
#include <vector>
#include "Math.h"
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
	virtual void onAnimCompleteEvent(const std::string& animName);

	void addComponent(class Component* component);
	void removeComponent(class Component* component);
	State getState()const;
	const Vector2& getPosition()const;
	float getScale()const;
	float getRotation()const;
	class Game* getGame();
	
	void setPosition(const Vector2& position) { this->m_Position = position; }
	void setScale(float scale) { this->m_Scale = scale; }
	void setRotation(float rotation) { this->m_Rotation = rotation; }

	void setState(State state) { this->m_State = state; }



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

inline const Vector2 & Actor::getPosition() const
{
	return this->m_Position;
}

inline float Actor::getScale() const
{
	return this->m_Scale;
}

inline float Actor::getRotation() const
{
	return this->m_Rotation;
}


inline Game * Actor::getGame()
{
	return this->m_Game;
}


