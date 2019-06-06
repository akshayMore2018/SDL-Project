#include "Game.h"

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
			"OstenGate",
			100,
			100,
			1024,
			768,
			0
		);

		if (!this->m_Window)
		{
			SDL_Log("WSDL window creation failed :%s", SDL_GetError);
			return false;
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
	SDL_DestroyWindow(this->m_Window);
	SDL_Quit();
}

void Game::events()
{
}

void Game::update()
{
}

void Game::render()
{
}
