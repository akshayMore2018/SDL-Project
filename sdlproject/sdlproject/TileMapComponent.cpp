#include "TileMapComponent.h"
#include "Actor.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
TileMapComponent::TileMapComponent(Actor * owner, int draworder)
	:SpriteComponent(owner,draworder), tileWidth(16),tileHeight(16)
{

}

TileMapComponent::~TileMapComponent()
{
	for (auto i : this->tiles)
	{
		delete i;
	}
	this->tiles.clear();
}

void TileMapComponent::loadMap(const std::string & mapFile, const std::string& tileSet)
{
	this->setTexture(this->m_Owner->getGame()->getTexture(tileSet));

	horTileCount = m_TextureWidth / tileWidth;
	verTileCount = m_TextureHeight / tileHeight;
	std::ifstream file(mapFile.c_str());
	std::vector<int> cells;
	if (file.is_open())
	{
		std::string line;
		std::stringstream ss;
		int r=0, c=0;
		while(std::getline(file, line))
		{ 
			ss.str(line);
			int i;
			while (ss >> i)
			{
				
				cells.push_back(i);
				//due to incorrect tile rendering order , passing r into column argument and vice versa.
				this->tiles.push_back(new Tile(i, c, r, this));
				c++;
				if (ss.peek() == ',')
					ss.ignore();
			}
			ss.clear();
			r++;
			c = 0;
		}
	}
}

void TileMapComponent::draw(SDL_Renderer * renderer)
{
	if (this->m_Texture)
	{
		for (auto tile : tiles)
		{
			if (tile->ID == -1)
				continue;
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
