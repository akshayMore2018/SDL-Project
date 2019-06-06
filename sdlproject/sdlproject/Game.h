#pragma once
#include "SDL.h"
#include <vector>
class Game
{
public:
	Game();
	~Game();

	bool initialize();

	void run();

	void stop();

private:
	void addActor(class Actor* actor);
	void events();
	void update();
	void render();

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	bool m_UpdatingActors;
	std::vector<Actor*> m_PendingActors;
	std::vector<Actor*> m_Actors;
};