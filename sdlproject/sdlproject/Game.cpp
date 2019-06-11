#include "Game.h"
#include "Actor.h"
#include "SDL_image.h"
#include <iostream>
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Player.h"
#include "CollisionComponent.h"
#include "Tile.h"
Game::Game():m_Window(nullptr),m_IsRunning(true)
{
}

Game::~Game()
{
	
}

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO)==0)
	{
		this->m_Window = SDL_CreateWindow(
			"StarHopper",
			100,
			100,
			1024,
			768,
			0
		);

		if (!this->m_Window)
		{
			SDL_Log("SDL window creation failed :%s", SDL_GetError);
			return false;
		}

		this->m_Renderer = SDL_CreateRenderer(this->m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!this->m_Renderer)
		{
			SDL_Log("SDL renderer creation failed :%s", SDL_GetError());
			return false;
		}
		if (!IMG_Init(IMG_INIT_PNG))
		{
			SDL_Log("Failed to initialize SDL_image :%s", IMG_GetError());
			system("pause");
		}
		this->loadData();
		mTicksCount = SDL_GetTicks();
		return true;
	}
	SDL_Log("SDL initialization failed :%s", SDL_GetError);
	return false;
}

void Game::run()
{
	while (this->m_IsRunning)
	{
		events();
		update();
		render();
	}
}

void Game::stop()
{
	this->unloadData();
	IMG_Quit();
	SDL_DestroyRenderer(this->m_Renderer);
	SDL_DestroyWindow(this->m_Window);
	SDL_Quit();
}

void Game::addActor(Actor * actor)
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

void Game::removeActor(Actor * actor)
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

void Game::addSprite(SpriteComponent * sprite)
{
	int drawOrder = sprite->getDrawOrder();

	auto iter = this->m_Sprites.begin();
	for (;iter != this->m_Sprites.end(); iter++)
	{
		if (drawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	this->m_Sprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent * sprite)
{
	auto iter = std::find(this->m_Sprites.begin(), this->m_Sprites.end(), sprite);
	this->m_Sprites.erase(iter);
}

void Game::addCollider(CollisionComponent * collider)
{
	this->m_Colliders.push_back(collider);
}

void Game::removeCollider(CollisionComponent * collider)
{
	auto iter = std::find(this->m_Colliders.begin(), this->m_Colliders.end(), collider);
	this->m_Colliders.erase(iter);
}

SDL_Texture * Game::getTexture(const std::string & filename)
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

		texture = SDL_CreateTextureFromSurface(this->m_Renderer, surf);
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

void Game::addTile(Tile * tile)
{
	mTiles.emplace_back(tile);
}

void Game::removeTile(Tile * tile)
{
	auto iter = std::find(mTiles.begin(),
		mTiles.end(), tile);
	if (iter != mTiles.end())
	{
		mTiles.erase(iter);
	}
}

void Game::loadData()
{
	Player* player = new Player(this);
	player->init();

	
	for (int i = 0; i < 16; i++)
	{
		Tile* tile = new Tile(this);
		tile->setPosition(Vector2((i*64+32), 400.0f));
		tile->init();
	}

}

void Game::unloadData()
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

void Game::events()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			this->m_IsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		this->m_IsRunning = false;
	}

	this->m_UpdatingActors = true;
	for (auto actor : this->m_Actors)
	{
		actor->processInput(state);
	}
	this->m_UpdatingActors = false;
}

void Game::update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

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

void Game::render()
{
	SDL_SetRenderDrawColor(this->m_Renderer,12, 32, 32, 255);
	SDL_RenderClear(this->m_Renderer);
	for (auto sprite : m_Sprites)
	{
		sprite->draw(m_Renderer);
	}
	SDL_SetRenderDrawColor(this->m_Renderer, 255, 0, 0, 255);
	for (auto actor : m_Actors)
	{
		if (actor->getCollider())
		{
			SDL_RenderDrawRect(m_Renderer,&actor->getCollider()->getRect());
		}
		
	}

	SDL_RenderPresent(this->m_Renderer);
}
