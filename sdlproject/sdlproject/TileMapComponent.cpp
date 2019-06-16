#include "TileMapComponent.h"
#include "World.h"
#include "Tile.h"
#include <fstream>
#include <sstream>
#include "tinyxml2.h"
#include <map>

int TileMapComponent::tileWidth = 0;
int TileMapComponent::tileHeight = 0;
int TileMapComponent::xTiles = 0;
int TileMapComponent::yTiles = 0;
int TileMapComponent::mapWidth = 0;
int TileMapComponent::mapHeight = 0;

TileMapComponent::TileMapComponent(World * actor, int draworder)
	:SpriteComponent(actor,draworder),mWorld(actor)
{

}

TileMapComponent::~TileMapComponent()
{
	for (int i = 0; i < yTiles; i++)
	{
		for (int j = 0; j < xTiles; j++)
		{
			delete gridMap[j][i];
		}
	}
	gridMap.clear();
}

void TileMapComponent::loadMap(const std::string& mapFile)
{
	setTexture(mWorld->getGame()->getTexture("Assets/map/tileset.png"));

	std::string file = "Assets/map/map.tmx";
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

		gridMap.resize(xTiles);
		for (int i = 0; i < xTiles; i++)
		{
			gridMap.at(i).resize(yTiles, 0);
		}
		ss.clear();
		i = 0;

		int xImgTiles = m_TextureWidth / tileWidth;
		tinyxml2::XMLElement * layerElement = mapRoot->FirstChildElement("layer");
		while (layerElement != nullptr)
		{
			const char * layer = nullptr;
			layer = layerElement->Attribute("name");
			if (layer == nullptr) std::cout << "XML_ERROR_PARSING_LAYER_NAME" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
			std::string layerName = layer;

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

							Tile* tile;

							if (layerName == "solid")
							{
								tile = new Tile(Tile::SOLID, i);
							}
							else
							{
								tile = new Tile(Tile::BACKGROUND, i);
							}
							tile->init(c, r, tileWidth, tileHeight);
							tile->setImgSrcCoord(i % xImgTiles, i / xImgTiles);
							gridMap[c][r] = tile;

						}
						c++;
					}
					tile = tile->NextSiblingElement("tile");
				}

			}
			layerElement = layerElement->NextSiblingElement("layer");
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
		for (int i = 0; i < yTiles; i++)
		{
			for (int j = 0; j < xTiles; j++)
			{
				if (gridMap[j][i])
				{
					SDL_Rect dstRect, srcRect;
					dstRect.x = static_cast<int>(gridMap[j][i]->getPosition().x - World::camera.x);
					dstRect.y = static_cast<int>(gridMap[j][i]->getPosition().y - World::camera.y);
					dstRect.w = tileWidth;
					dstRect.h = tileHeight;

					srcRect.x = static_cast<int>(gridMap[j][i]->getImgSrc().x);
					srcRect.y = static_cast<int>(gridMap[j][i]->getImgSrc().y);
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

const Tile * TileMapComponent::getTile(int x, int y) const
{
	return gridMap[x][y];
}
