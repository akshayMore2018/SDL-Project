#include "Game.h"
#include "Actor.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "MenuView.h"
#include "GameView.h"
Game::Game():m_Window(nullptr),m_IsRunning(true)
{
}

Game::~Game()
{
	delete currentView;
}

bool Game::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO)==0)
	{
		this->m_Window = SDL_CreateWindow(
			"Aranyak",
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

		if (TTF_Init()!=0)
		{
			SDL_Log("Failed to initialize SDL_ttf :%s", TTF_GetError());
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
	TTF_Quit();
}

void Game::changeView(const short unsigned int viewID)
{
	switch (viewID)
	{
	case MENU:
		if (currentView)
		{
			currentView->exit();
		}
		currentView = new MenuView(this);
		currentView->enter();
		break;
	case GAMEPLAY:
		if (currentView)
		{
			currentView->exit();
		}
		currentView = new GameView(this);
		currentView->enter();
		break;
	default:
		stop();
		break;
	}

}



void Game::loadData()
{
	changeView(MENU);
}

void Game::unloadData()
{
	if(currentView)
	currentView->exit();
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
	if (currentView)
	currentView->events();
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

	if (currentView)
	currentView->update(deltaTime);

}

void Game::render()
{
	SDL_SetRenderDrawColor(this->m_Renderer,12, 32, 32, 255);
	SDL_RenderClear(this->m_Renderer);

	if (currentView)
	currentView->render();
	SDL_RenderPresent(this->m_Renderer);
}
