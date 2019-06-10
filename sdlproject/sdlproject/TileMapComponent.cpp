#include "TileMapComponent.h"
#include "Actor.h"
#include "Game.h"
#include <iostream>
TileMapComponent::TileMapComponent(Actor * owner, int draworder)
	:SpriteComponent(owner,draworder), tileWidth(16),tileHeight(16)
{

}

void TileMapComponent::loadMap(const std::string & mapFile, const std::string& tileSet)
{
	this->setTexture(this->m_Owner->getGame()->getTexture(tileSet));

	horTileCount = m_TextureWidth / tileWidth;
	verTileCount = m_TextureHeight / tileHeight;

	this->tiles.push_back(new Tile(200, 18, 33, horTileCount));
	this->tiles.push_back(new Tile(201, 19, 33, horTileCount));
	
	this->tiles.push_back(new Tile(220, 18, 34, horTileCount));
	this->tiles.push_back(new Tile(221, 19, 34, horTileCount));

	this->tiles.push_back(new Tile(200, 20, 33, horTileCount));
	this->tiles.push_back(new Tile(201, 21, 33, horTileCount));
	
	this->tiles.push_back(new Tile(220, 20, 34, horTileCount));
	this->tiles.push_back(new Tile(221, 21, 34, horTileCount));

	this->tiles.push_back(new Tile(200, 22, 33, horTileCount));
	this->tiles.push_back(new Tile(201, 23, 33, horTileCount));
	
	this->tiles.push_back(new Tile(220, 22, 34, horTileCount));
	this->tiles.push_back(new Tile(221, 23, 34, horTileCount));

}

void TileMapComponent::draw(SDL_Renderer * renderer)
{
	if (this->m_Texture)
	{
		for (auto tile : tiles)
		{
			SDL_RenderCopyEx(
				renderer,
				this->m_Texture,
				&tile->src,
				&tile->dst,
				0,
				nullptr,
				SDL_RendererFlip::SDL_FLIP_NONE
			);

		}
	}
}
