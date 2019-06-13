#include "TileMapComponent.h"
#include "World.h"
#include "Tile.h"
TileMapComponent::TileMapComponent(World * actor, int draworder)
	:SpriteComponent(actor,draworder),mWorld(actor)
{

}

void TileMapComponent::loadMap()
{
	setTexture(mWorld->getGame()->getTexture("Assets/map/metaTile.png"));
	for (int i = 30; i < mWorld->getYTiles(); i++)
	{
		for (int j = 0; j < mWorld->getXTiles(); j++)
		{
			Tile* tile = new Tile("Tile");
			tile->setPosition((j * 16), (i * 16));
			tile->init();
			mWorld->addTile(j, i, tile);
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
		for (int i = 30; i < mWorld->getYTiles(); i++)
		{
			for (int j = 0; j < mWorld->getXTiles(); j++)
			{
				SDL_Rect rect;
				rect.x = static_cast<int>(mWorld->GetTile(j, i)->getPosition().x);
				rect.y = static_cast<int>(mWorld->GetTile(j, i)->getPosition().y);
				rect.w = mWorld->GetTile(j, i)->getWidth();
				rect.h = mWorld->GetTile(j, i)->getHeight();

				SDL_RenderCopyEx(renderer,
					this->m_Texture,
					nullptr,
					&rect,
					0,
					nullptr,
					SDL_FLIP_NONE);
			}
		}
	}
}
