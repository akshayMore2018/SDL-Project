#pragma once
#include "Component.h"
#include "SDL.h"
class CollisionComponent : public Component
{
public:
	CollisionComponent(class Actor* owner , int updateOrder = 100);
	~CollisionComponent();
	virtual void draw(SDL_Renderer* renderer);
	virtual void update(float deltaTime);
	void updateObjectBounds();
	
	void setRectLocal(float x, float y, float width, float height);
	const float getLeft()const { return left; }
	const float getRight()const { return right; }
	const float getTop()const { return top; }
	const float getBottom()const { return bottom; }

private:
	SDL_Rect collisionRect;
	float localX, localY;
	float left, right, top, bottom;
};