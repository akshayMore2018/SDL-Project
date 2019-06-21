#include "GameView.h"
#include "Game.h"
#include "BGSpriteComponent.h"
#include "SDL_image.h"
#include "Player.h"
#include "World.h"
#include <iostream>
#include "ScreenLoading.h"


GameView::GameView(Game * game)
	:View(game), gameLoaded(false)
{
	std::cout << "Loading textures......" << std::endl;
	getTexture("Assets/background/background.png");
	getTexture("Assets/background/middleground.png");
	getTexture("Assets/background/foreground.png");
	getTexture("Assets/playerAnimSheets/run0.png");
	getTexture("Assets/playerAnimSheets/jump.png");
	getTexture("Assets/playerAnimSheets/fall.png");
	getTexture("Assets/playerAnimSheets/idle0.png");
	getTexture("Assets/map/tileset.png");
}

void GameView::init()
{
	std::cout << "Thread running.." << std::endl;
	gameLoaded = false;
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
	gameLoaded = true;
}

void GameView::enter()
{
	//setScreen(loadingScreen);
	setScreen(new ScreenLoading(Screen::LOAD, this));
}

void GameView::exit()
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

void GameView::addSprite(SpriteComponent * sprite)
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

void GameView::removeSprite(SpriteComponent * sprite)
{
	auto iter = std::find(this->m_Sprites.begin(), this->m_Sprites.end(), sprite);
	this->m_Sprites.erase(iter);
}

void GameView::addCollider(CollisionComponent * collider)
{
	this->m_Colliders.push_back(collider);
}

void GameView::removeCollider(CollisionComponent * collider)
{
	auto iter = std::find(this->m_Colliders.begin(), this->m_Colliders.end(), collider);
	this->m_Colliders.erase(iter);
}

void GameView::addRay(RayComponent * ray)
{
	this->m_Rays.push_back(ray);
}

void GameView::removeRay(RayComponent * ray)
{
	auto iter = std::find(this->m_Rays.begin(), this->m_Rays.end(), ray);
	this->m_Rays.erase(iter);
}

void GameView::addActor(Actor * actor)
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

void GameView::removeActor(Actor * actor)
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




void GameView::events()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (currentScreen != nullptr)
	{
		currentScreen->events();
		return;
	}


	this->m_UpdatingActors = true;
	for (auto actor : this->m_Actors)
	{
		actor->processInput(state);
	}
	this->m_UpdatingActors = false;
}

void GameView::update(float deltaTime)
{

	if (currentScreen != nullptr)
	{
		currentScreen->update(deltaTime);
		return;
	}

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

void GameView::render()
{
	if (currentScreen != nullptr)
	{
		currentScreen->render();
		return;
	}


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

