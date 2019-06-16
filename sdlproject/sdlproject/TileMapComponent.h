#pragma once
#include "SpriteComponent.h"
#include <iostream>
#include <vector>
class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class World* actor, int draworder = 50);
	~TileMapComponent();
	void loadMap(const std::string& mapFile);

	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	static  int tileWidth;
	static  int tileHeight;
	static  int xTiles;
	static  int yTiles;
	static  int mapWidth;
	static  int mapHeight;

	const class Tile* getTile(int x, int y)const;


private:
	class World* mWorld;
	std::vector<std::vector<class Tile*>> gridMap;
};