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

	std::string file = "Assets/map/map.tmx";
	int tileWidth;
	int tileHeight;
	int xTiles;
	int yTiles;
	int mapWidth;
	int mapHeight;

	//xml parsing
	tinyxml2::XMLDocument doc;
	doc.LoadFile(file.c_str());
	tinyxml2::XMLNode * mapRoot = doc.FirstChildElement("map");
	if (mapRoot == nullptr)
	{
		std::cout << "XML_ERROR_FILE_READ_ERROR :" << tinyxml2::XML_ERROR_FILE_READ_ERROR << std::endl;
	}
	else
	{
		std::stringstream ss;
		int i = 0;
		const char * temp = nullptr;
		temp = doc.FirstChildElement("map")->Attribute("width");
		if (temp!=nullptr)
		{
			ss.str(temp);
			ss >> i;
			xTiles = i;
			ss.clear();
		}
		else
		{
			std::cout << "XML_ERROR_PARSING_MAP_XTILES" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
		}
		
		temp = doc.FirstChildElement("map")->Attribute("height");

		if (temp != nullptr)
		{
			ss.str(temp);
			ss >> i;
			yTiles = i;
			ss.clear();
		}
		else
		{
			std::cout << "XML_ERROR_PARSING_MAP_YTILES" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
		}

		temp = doc.FirstChildElement("map")->Attribute("tilewidth");

		if (temp != nullptr)
		{
			ss.str(temp);
			ss >> i;
			tileWidth = i;
			ss.clear();
		}
		else
		{
			std::cout << "XML_ERROR_PARSING_MAP_TILEWIDTH" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
		}

		temp = doc.FirstChildElement("map")->Attribute("tileheight");

		if (temp != nullptr)
		{
			ss.str(temp);
			ss >> i;
			tileHeight = i;
			ss.clear();
		}
		else
		{
			std::cout << "XML_ERROR_PARSING_MAP_TILEHEIGHT" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
		}

		mapWidth = xTiles * tileWidth;
		mapHeight = yTiles * tileHeight;

		std::cout << "tileWidth :" << tileWidth << std::endl;
		std::cout << "tileHeight :" << tileHeight << std::endl;
		std::cout << "xTiles :" << xTiles << std::endl;
		std::cout << "yTiles :" << yTiles << std::endl;
		std::cout << "mapWidth :" << mapWidth << std::endl;
		std::cout << "mapHeight :" << mapHeight << std::endl;

		ss.clear();
		i = 0;

		int xImgTiles = m_TextureWidth / tileWidth;
		tinyxml2::XMLElement * layerElement = mapRoot->FirstChildElement("layer");
		if (layerElement != nullptr)
		{
			const char * layer = nullptr;
			layer = layerElement->Attribute("name");
			if (layer == nullptr) std::cout << "XML_ERROR_PARSING_LAYER_NAME" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
			std::string layerName = layer;
			std::cout << layerName.c_str() << std::endl;

			tinyxml2::XMLElement * dataTag;
			dataTag = layerElement->FirstChildElement("data");

			if (dataTag != nullptr)
			{
				tinyxml2::XMLElement * tile = dataTag->FirstChildElement("tile");

				int r = 0, c = 0;
				while (tile != nullptr)
				{
					if (tile == nullptr)
					{
						std::cout << "XML_ERROR_PARSING_ELEMENT_TILE" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
					}
					else
					{
						if (c > (xTiles - 1))
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
						c++;
					}
					tile = tile->NextSiblingElement("tile");
				}

			}
			//layerElement = layerElement->NextSiblingElement("layer");
		}
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
