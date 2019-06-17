#include "TileMapComponent.h"
#include "World.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include "tinyxml2.h"

TileMapComponent::TileMapComponent(World * actor, int draworder)
	:SpriteComponent(actor,draworder)
{
	dstRect.w = World::tileWidth;
	dstRect.h = World::tileHeight;
	srcRect.w = World::tileWidth;
	srcRect.h = World::tileHeight;
}

TileMapComponent::~TileMapComponent()
{
	for (int i = 0; i < World::yTiles; i++)
	{
		for (int j = 0; j < World::xTiles; j++)
		{
			delete gridMap[j][i];
		}
	}
	gridMap.clear();
}

void TileMapComponent::update(float deltaTime)
{
}

void TileMapComponent::draw(SDL_Renderer * renderer)
{
	if (m_Texture)
	{
		for (int i = 0; i < World::yTiles; i++)
		{
			for (int j = 0; j < World::xTiles; j++)
			{
				if (gridMap[j][i])
				{
					dstRect.x = static_cast<int>(gridMap[j][i]->getPosition().x - World::camera.x);
					dstRect.y = static_cast<int>(gridMap[j][i]->getPosition().y - World::camera.y);
				
					srcRect.x = static_cast<int>(gridMap[j][i]->getImgSrc().x);
					srcRect.y = static_cast<int>(gridMap[j][i]->getImgSrc().y);
					
					SDL_RenderCopyEx(renderer,
						this->m_Texture,
						&srcRect,
						&dstRect,
						0,
						nullptr,
						SDL_FLIP_NONE);
				}
				

			}
		}
	}
}

const Tile * TileMapComponent::getTile(int x, int y) const
{
	return gridMap[x][y];
}

void TileMapComponent::setTiles(std::vector<std::vector<class Tile*>>& tiles)
{
	gridMap = tiles;
}
