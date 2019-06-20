#pragma once
#include "SDL.h"
#include <vector>
#include <unordered_map>
class Game
{
public:
	Game();
	~Game();
	bool initialize();
	void run();
	void stop();
	SDL_Renderer* m_Renderer;

private:
	void loadData();
	void unloadData();
	void events();
	void update();
	void render();
	SDL_Window* m_Window;	
	bool m_IsRunning;
	Uint32 mTicksCount;
	class View* currentView;
};