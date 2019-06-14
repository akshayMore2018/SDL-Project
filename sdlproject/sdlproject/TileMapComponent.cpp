#include "TileMapComponent.h"
#include "World.h"
#include "Tile.h"
#include <fstream>
#include <sstream>

const int TileMapComponent::tileWidth = 16;
const int TileMapComponent::tileHeight = 16;

TileMapComponent::TileMapComponent(World * actor, int draworder)
	:SpriteComponent(actor,draworder),mWorld(actor)
{

}

TileMapComponent::~TileMapComponent()
{

}

void TileMapComponent::loadMap()
{
	setTexture(mWorld->getGame()->getTexture("Assets/map/tileset.png"));
	std::ifstream file("Assets/map/map.csv");
	int xImgTiles = m_TextureWidth / tileWidth;
	if (file.is_open())
	{
		std::string line;
		std::stringstream ss;
		int r = 0, c = 0;
		while (std::getline(file, line))
		{
			ss.str(line);
			int i;
			while (ss >> i)
			{
				//due to incorrect tile rendering order , passing r into column argument and vice versa.
				Tile* tile = new Tile("solid", i);
				tile->init(c, r, tileWidth, tileHeight);
				tile->setImgSrcCoord(i % xImgTiles, i / xImgTiles);
				mWorld->addTile(c, r, tile);

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

void TileMapComponent::update(float deltaTime)
{
}

void TileMapComponent::draw(SDL_Renderer * renderer)
{
	if (m_Texture)
	{
		for (int i = 0; i < mWorld->getYTiles(); i++)
		{
			for (int j = 0; j < mWorld->getXTiles(); j++)
			{
				if (mWorld->getTile(j, i)->getTileID() == -1)
					continue;
				SDL_Rect dstRect, srcRect;
				dstRect.x = static_cast<int>(mWorld->getTile(j, i)->getPosition().x - World::camera.x);
				dstRect.y = static_cast<int>(mWorld->getTile(j, i)->getPosition().y - World::camera.y);
				dstRect.w = tileWidth;
				dstRect.h = tileHeight;

				srcRect.x = static_cast<int>(mWorld->getTile(j, i)->getImgSrc().x);
				srcRect.y = static_cast<int>(mWorld->getTile(j, i)->getImgSrc().y);
				srcRect.w = tileWidth;
				srcRect.h = tileHeight;

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
