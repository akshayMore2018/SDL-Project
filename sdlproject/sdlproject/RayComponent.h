#pragma once
#include "Component.h"
#include "SDL.h"
#include <vector>
#include "Math.h"
class RayComponent : public Component
{
public:
	enum RAY
	{
		BOTTOM,
		LEFT,
		RIGHT
	};

	RayComponent(class Actor* owner ,RAY type,int updateOrder=100);
	~RayComponent();
	void draw(SDL_Renderer* renderer);
	void update(float deltaTime);
private:
	std::vector<class Vector2> points;
	Vector2 rayPoint;
	Vector2 position;
	short unsigned int rayType;
	bool canPointBeTravelled(int x, int y);
};