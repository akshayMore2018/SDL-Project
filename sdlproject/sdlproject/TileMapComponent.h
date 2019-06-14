#pragma once
#include "SpriteComponent.h"

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class World* actor, int draworder = 10);
	~TileMapComponent();
	void loadMap();

	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	static const int tileWidth;
	static const int tileHeight;

private:
	class World* mWorld;
};