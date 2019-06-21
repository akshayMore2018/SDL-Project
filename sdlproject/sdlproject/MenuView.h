#pragma once
#include "View.h"
class MenuView : public View
{
public:
	MenuView(class Game* game);

	void enter();
	void exit();
	void events();
	void update(float deltaTime);
	void render();

private:
	SDL_Texture* bg;
	SDL_Texture* mg;
};