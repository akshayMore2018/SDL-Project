#include "TileMapComponent.h"
#include "World.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include "tinyxml2.h"

TileMapComponent::TileMapComponent(Tile * actor, int draworder)
	:SpriteComponent(actor,draworder), m_Owner(actor)
{
	dstRect.w = World::tileWidth;
	dstRect.h = World::tileHeight;
	srcRect.w = World::tileWidth;
	srcRect.h = World::tileHeight;
}

TileMapComponent::~TileMapComponent()
{

}

void TileMapComponent::update(float deltaTime)
{
}

void TileMapComponent::draw(SDL_Renderer * renderer)
{
	if (m_Texture)
	{
		{
			dstRect.x = static_cast<int>(m_Owner->getPosition().x - World::camera.x);
			dstRect.y = static_cast<int>(m_Owner->getPosition().y - World::camera.y);
				
			srcRect.x = static_cast<int>(m_Owner->getImgSrc().x);
			srcRect.y = static_cast<int>(m_Owner->getImgSrc().y);
					
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
