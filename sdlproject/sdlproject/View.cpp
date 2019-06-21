#include "View.h"
#include "SDL_image.h"
#include "Player.h"
#include "World.h"
#include "BGSpriteComponent.h"
#include "RayComponent.h"
#include "CollisionComponent.h"
#include "Screen.h"

View::View(Game * game)
	:mGame(game),currentScreen(nullptr)
{
}

void View::enter()
{
}

void View::exit()
{

}

void View::events()
{
}

void View::update(float deltaTime)
{
}

void View::render()
{
}

void View::setScreen(Screen * screen)
{
	if (currentScreen != nullptr)
	{
		currentScreen->exit();
		currentScreen = nullptr;
	}
	currentScreen = screen;
	if (currentScreen != nullptr)
		currentScreen->enter();
}


SDL_Texture * View::getTexture(const std::string & filename)
{
	SDL_Texture* texture = nullptr;
	auto iter = this->m_Textures.find(filename);

	if (iter != this->m_Textures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surf = IMG_Load(filename.c_str());

		if (!surf)
		{
			SDL_Log("Failed to load texture file : %s", filename.c_str());
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(this->mGame->m_Renderer, surf);
		SDL_FreeSurface(surf);

		if (!texture)
		{
			SDL_Log("failed to convert surface to texture for %s", filename.c_str());
			return nullptr;
		}

		this->m_Textures.emplace(filename.c_str(), texture);

	}

	return texture;
}


