#pragma once
#include "Screen.h"
#include "SDL.h"

extern "C" int loadMap(void* data);
class ScreenLoading :public Screen
{
public:
	friend int loadMap(void* data);
	ScreenLoading(short unsigned int ID,class GameView* view);

	void enter();

	void events();
	void update(float deltaTime);
	void render();

	void exit();

private:
	class GameView* mView;
	int threadReturnValue;
	SDL_Thread* threadID;
	SDL_Texture* spinner;
	float angle;
};