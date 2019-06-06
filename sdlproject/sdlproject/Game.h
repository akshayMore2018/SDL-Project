#pragma once
#include "SDL.h"
class Game
{
public:
	Game();
	~Game();

	bool initialize();

	void run();

	void stop();

private:

	void events();
	void update();
	void render();

	SDL_Window* m_Window;
	bool m_IsRunning;
	
};