#include "TileMapComponent.h"
#include "World.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include "tinyxml2.h"
#include <map>

const int TileMapComponent::tileWidth = 16;
const int TileMapComponent::tileHeight = 16;

TileMapComponent::TileMapComponent(World * actor, int draworder)
	:SpriteComponent(actor,draworder),mWorld(actor)
{

}

TileMapComponent::~TileMapComponent()
{

}

void TileMapComponent::loadMap(const std::string& mapFile)
{
	setTexture(mWorld->getGame()->getTexture("Assets/map/tileset.png"));

	std::map<std::string, std::string> mapData;
	int xImgTiles = m_TextureWidth / tileWidth;
	//xml parsing
	tinyxml2::XMLDocument doc;
	doc.LoadFile("Assets/map/map.tmx");
	tinyxml2::XMLNode * pRoot = doc.FirstChild();
	if (pRoot == nullptr)
	{
		std::cout << "XML_ERROR_FILE_READ_ERROR :" << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
	}
	tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("layer");
	if (pElement != nullptr)
	{
		const char * layer = nullptr;
		layer = pElement->Attribute("name");
		if (layer == nullptr) std::cout << "XML_ERROR_PARSING_LAYER_NAME" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
		std::string layerName = layer;
		std::cout << layerName.c_str() << std::endl;

		tinyxml2::XMLElement * dataTag;
		dataTag = pElement->FirstChildElement("data");

		if (dataTag != nullptr)
		{
			tinyxml2::XMLElement * tile = dataTag->FirstChildElement("tile");
			
			int r = 0, c = 0;
			std::stringstream ss;
			int i = 0;
			while (tile != nullptr)
			{
				if (tile == nullptr)
				{
					std::cout << "XML_ERROR_PARSING_ELEMENT_TILE" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
				}
				else
				{
					if (c > 149)
					{
						c = 0;
						r++;
					}
					
					const char * tilegid = nullptr;
					tilegid = tile->Attribute("gid");
					if (tilegid != nullptr)
					{
						ss.str(tilegid);
						ss >> i;
						ss.clear();
						i--;

						Tile* tile = new Tile(Tile::SOLID, i);
						tile->init(c, r, tileWidth, tileHeight);
						tile->setImgSrcCoord(i % xImgTiles, i / xImgTiles);
						mWorld->addTile(c, r, tile);

					}
					

					std::cout << "c :" << c << " r:" << r << std::endl;
					c++;
				}

				tile = tile->NextSiblingElement("tile");
			}
			
		}
		//pElement = pElement->NextSiblingElement("layer");
	}
	doc.Clear();

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
				if (mWorld->getTile(j, i))
				{
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
}
