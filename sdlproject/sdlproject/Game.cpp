#include "Game.h"
#include "Actor.h"
#include "SDL_image.h"
#include <iostream>

Game::Game():m_Window(nullptr),m_IsRunning(true),frameStart(0),frameTime(0)
{
}

Game::~Game()
{
	while (!this->m_Actors.empty())
	{
		delete this->m_Actors.back();
	}
}

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO)==0)
	{
		this->m_Window = SDL_CreateWindow(
			"OstenGate",
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
}

void Game::update()
{
	frameStart = SDL_GetTicks();
	// update game

	this->m_UpdatingActors = true;
	for (auto actor : this->m_Actors)
	{
		actor->update(frameTime);
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

	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime)
	{
		SDL_Delay(frameDelay - frameTime);
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(this->m_Renderer,32, 32, 32, 255);
	SDL_RenderClear(this->m_Renderer);

	SDL_RenderPresent(this->m_Renderer);
}
