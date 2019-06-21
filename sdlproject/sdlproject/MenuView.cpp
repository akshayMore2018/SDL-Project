#include "MenuView.h"
#include "Game.h"
#include <iostream>

MenuView::MenuView(Game * game)
	:View(game)
{
}

void MenuView::enter()
{
	bg = getTexture("Assets/background/background.png");
}

void MenuView::exit()
{
}

void MenuView::events()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (state[SDL_SCANCODE_SPACE])
	{
		this->mGame->changeView(Game::GAMEPLAY);
	}
}

void MenuView::update(float deltaTime)
{
}

void MenuView::render()
{
	SDL_Rect rect={ 0,0,1024,768 };
	SDL_RenderCopy(this->mGame->m_Renderer,bg,nullptr,&rect);
}
