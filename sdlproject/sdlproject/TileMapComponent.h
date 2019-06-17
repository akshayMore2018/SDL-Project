#pragma once
#include "SpriteComponent.h"
#include <iostream>
#include <vector>
class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class World* actor, int draworder = 50);
	~TileMapComponent();

	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	const class Tile* getTile(int x, int y)const;
	void setTiles(std::vector<std::vector<class Tile*>>& tiles);

private:
	SDL_Rect dstRect, srcRect;
	std::vector<std::vector<class Tile*>> gridMap;
};