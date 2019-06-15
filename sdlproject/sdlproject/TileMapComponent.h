#pragma once
#include "SpriteComponent.h"
#include <iostream>
class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class World* actor, int draworder = 50);
	~TileMapComponent();
	void loadMap(const std::string& mapFile);

	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	static const int tileWidth;
	static const int tileHeight;

private:
	class World* mWorld;
};