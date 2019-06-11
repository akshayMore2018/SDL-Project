#pragma once
#include "Component.h"
#include "SDL.h"
#include <vector>
class RayComponent : public Component
{
public:
	RayComponent(class Actor* owner , int updateOrder=100);
	~RayComponent();
	void draw(SDL_Renderer* renderer);
	void update(float deltaTime);

private:
	std::vector<class Vector2> points;

};