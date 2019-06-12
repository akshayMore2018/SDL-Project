#pragma once
#include "Component.h"
#include "SDL.h"
#include <vector>
#include "Math.h"
class RayComponent : public Component
{
public:
	RayComponent(class Actor* owner , int updateOrder=100);
	~RayComponent();
	void draw(SDL_Renderer* renderer);
	void update(float deltaTime);
	const class Tile* getTile()const;

private:
	std::vector<class Vector2> points;
	Vector2 rayPoint;
	Vector2 position;

	bool canPointBeTravelled(int x, int y);
};