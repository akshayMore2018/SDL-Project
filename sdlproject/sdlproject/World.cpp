#include "World.h"
#include "Math.h"
#include "Tile.h"
#include "TileMapComponent.h"
#include "tinyxml2.h"
#include <sstream>

SDL_Rect World::camera = { 0,0,1024,768 };
int World::tileWidth = 0;
int World::tileHeight = 0;
int World::xTiles = 0;
int World::yTiles = 0;
int World::mapWidth = 0;
int World::mapHeight = 0;


World::World(const std::string& ID, class Game* game):
Actor(ID,game)
{

}

World::~World()
{
	
}

void World::updateActor(float deltaTime)
{
	camera.x = mPlayer->getPosition().x - camera.w / 2;
	camera.y = mPlayer->getPosition().y - camera.h / 2;

	if (camera.x < 0)camera.x = 0;
	if (camera.y < 0)camera.y = 0;

	if ((camera.x + camera.w) > mapWidth)camera.x = mapWidth - camera.w;
	if ((camera.y + camera.h) > mapHeight)camera.y = mapHeight - camera.h;
}

void World::init()
{
	loadMap("Assets/map/map.tmx");
	onemap = new TileMapComponent(this);
	onemap->setTexture(getGame()->getTexture("Assets/map/tileset.png"));
	onemap->setTiles(map["background"]);

	/*onemap = new TileMapComponent(this,102);
	onemap->setTexture(getGame()->getTexture("Assets/map/tileset.png"));
	onemap->setTiles(map["foreground"]);
*/
	onemap = new TileMapComponent(this);
	onemap->setTexture(getGame()->getTexture("Assets/map/tileset.png"));
	onemap->setTiles(map["solid"]);

}
void World::setPlayer(Actor * player)
{
	this->mPlayer = player;
}

void World::loadMap(const std::string& file)
{
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
		if (temp != nullptr)
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

		int xImgTiles = 864 / tileWidth;
		tinyxml2::XMLElement * layerElement = mapRoot->FirstChildElement("layer");
		while (layerElement != nullptr)
		{
			const char * layer = nullptr;
			layer = layerElement->Attribute("name");
			if (layer == nullptr) std::cout << "XML_ERROR_PARSING_LAYER_NAME" << tinyxml2::XML_ERROR_PARSING_ATTRIBUTE << std::endl;
			std::string layerName = layer;

			map[layerName].resize(xTiles);
			for (int i = 0; i < xTiles; i++)
			{
				map[layerName].at(i).resize(yTiles, 0);
			}

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

							if (layerName == "foreground")
							{
								tile = new Tile(FOREGROUND, i);
							}
							else if("middleground")
							{
								tile = new Tile(MIDDLEGROUND, i);
							}
							else if ("background")
							{
								tile = new Tile(BACKGROUND, i);
							}
							else
							{
								tile = new Tile(SOLID, i);
							}
							tile->init(c, r, tileWidth, tileHeight);
							tile->setImgSrcCoord(i % xImgTiles, i / xImgTiles);
							map[layerName][c][r] = tile;
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

