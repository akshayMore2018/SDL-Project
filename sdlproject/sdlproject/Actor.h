#pragma once
#include "SDL.h"
#include <vector>
#include "Math.h"
#include "CollisionComponent.h"
class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(const std::string& ID,class Game* game);
	virtual ~Actor();

	void update(float deltaTime);
	void updateComponent(float deltaTime);
	virtual void updateActor(float deltaTime);
	virtual void onAnimCompleteEvent(const std::string& animName);
	virtual void actorInput(const uint8_t* keystate);
	void processInput(const uint8_t* keystate);
	void addComponent(class Component* component);
	void removeComponent(class Component* component);
	
//	setters
	State getState()const;
	void setPosition(const Vector2& position) { this->m_Position = position; }
	void setScale(float scale) { this->m_Scale = scale; }
	void setRotation(float rotation) { this->m_Rotation = rotation; }
	void setState(State state) { this->m_State = state; }
	

	//getters
	const Vector2& getPosition()const;
	float getScale()const;
	float getRotation()const;
	class Game* getGame();
	const std::string& getID()const { return ID; }
	const float getLeft() const { return left; }
	const float getRight() const { return right; }
	const float getTop() const { return top; }
	const float getBottom() const { return bottom; }
	void updateObjectBounds();

	virtual void rayCastResult(Vector2 position);

	SDL_RendererFlip flipStateX;
protected:
	class CollisionComponent* collider;
	std::string ID;

private:
	State m_State;
	Vector2 m_Position;
	float m_Scale;
	float m_Rotation;
	std::vector<class Component*> m_Components;
	class Game* m_Game;
	float left, right, top, bottom;
	
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




