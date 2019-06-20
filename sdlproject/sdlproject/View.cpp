#include "View.h"
#include "SDL_image.h"
#include "Player.h"
#include "World.h"
#include "BGSpriteComponent.h"
#include "RayComponent.h"
#include "CollisionComponent.h"

View::View(Game * game)
	:mGame(game)
{
}

void View::addSprite(SpriteComponent * sprite)
{
	int drawOrder = sprite->getDrawOrder();

	auto iter = this->m_Sprites.begin();
	for (; iter != this->m_Sprites.end(); iter++)
	{
		if (drawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	this->m_Sprites.insert(iter, sprite);
}

void View::removeSprite(SpriteComponent * sprite)
{
	auto iter = std::find(this->m_Sprites.begin(), this->m_Sprites.end(), sprite);
	this->m_Sprites.erase(iter);
}

void View::addCollider(CollisionComponent * collider)
{
	this->m_Colliders.push_back(collider);
}

void View::removeCollider(CollisionComponent * collider)
{
	auto iter = std::find(this->m_Colliders.begin(), this->m_Colliders.end(), collider);
	this->m_Colliders.erase(iter);
}

void View::addRay(RayComponent * ray)
{
	this->m_Rays.push_back(ray);
}

void View::removeRay(RayComponent * ray)
{
	auto iter = std::find(this->m_Rays.begin(), this->m_Rays.end(), ray);
	this->m_Rays.erase(iter);
}

void View::addActor(Actor * actor)
{
	if (this->m_UpdatingActors)
	{
		this->m_PendingActors.emplace_back(actor);
	}
	else
	{
		this->m_Actors.emplace_back(actor);
	}
}

void View::removeActor(Actor * actor)
{
	auto iter = std::find(this->m_PendingActors.begin(), this->m_PendingActors.end(), actor);
	if (iter != this->m_PendingActors.end())
	{
		std::iter_swap(iter, this->m_PendingActors.end() - 1);
		this->m_PendingActors.pop_back();
	}

	iter = std::find(this->m_Actors.begin(), this->m_Actors.end(), actor);
	if (iter != this->m_Actors.end())
	{
		std::iter_swap(iter, this->m_Actors.end() - 1);
		this->m_Actors.pop_back();
	}
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

void View::loadData()
{
	Player* player = new Player("Player", this);
	player->init();

	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(player, 10);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		getTexture("Assets/background/background.png"),
		getTexture("Assets/background/background.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(25.0f);
	// Create the closer background
	bg = new BGSpriteComponent(player, 30);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		getTexture("Assets/background/middleground.png"),
		getTexture("Assets/background/middleground.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(50.0f);

	bg = new BGSpriteComponent(player, 111);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		getTexture("Assets/background/foreground.png"),
		getTexture("Assets/background/foreground.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(200.0f);


	mWorld = new World("map", this);
	mWorld->setPosition(Vector2(0, 0));
	mWorld->setPlayer(player);
	mWorld->init();
}

void View::unloadData()
{
	while (!this->m_Actors.empty())
	{
		delete this->m_Actors.back();
	}

	for (auto i : this->m_Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	this->m_Textures.clear();
}

void View::events()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	this->m_UpdatingActors = true;
	for (auto actor : this->m_Actors)
	{
		actor->processInput(state);
	}
	this->m_UpdatingActors = false;
}

void View::update(float deltaTime)
{
	this->m_UpdatingActors = true;
	for (auto actor : this->m_Actors)
	{
		actor->update(deltaTime);
	}
	this->m_UpdatingActors = false;

	for (auto pendingActor : this->m_PendingActors)
	{
		this->m_Actors.emplace_back(pendingActor);
	}
	this->m_PendingActors.clear();

	std::vector<Actor*> deadActors;

	for (auto actor : this->m_Actors)
	{
		if (actor->getState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}


	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void View::render()
{
	for (auto sprite : m_Sprites)
	{
		sprite->draw(this->mGame->m_Renderer);
	}
	SDL_SetRenderDrawColor(this->mGame->m_Renderer, 255, 0, 0, 255);

	/*for (auto collider : m_Colliders)
	{
		collider->draw(this->mGame->m_Renderer);
	}
	for (auto ray : m_Rays)
	{
		ray->draw(this->mGame->m_Renderer);
	}*/
}
