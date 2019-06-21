#include "MenuView.h"
#include "Game.h"
#include <iostream>
#include "Font.h"

MenuView::MenuView(Game * game)
	:View(game)
{

}

void MenuView::enter()
{
	bg = getTexture("Assets/background/background.png");
	mg = getTexture("Assets/background/middleground.png");
	title = getTexture("Assets/gui/title.png");
	font = new Font(getGame());
	font->load("Assets/fonts/m5x7/m5x7.ttf");
	font->RenderText("Press Start", 48);
	font->setFontPosition(512 - font->getFontWidth() / 2, 650);
}

void MenuView::exit()
{
	for (auto i : this->m_Textures)
	{
		SDL_DestroyTexture(i.second);
	}
	this->m_Textures.clear();
}

void MenuView::events()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (state[SDL_SCANCODE_RETURN])
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
	SDL_Rect titleRect = { 260,300,523,91 };
	SDL_RenderCopy(this->mGame->m_Renderer,bg,nullptr,&rect);
	SDL_RenderCopy(this->mGame->m_Renderer, mg, nullptr, &rect);
	SDL_RenderCopy(this->mGame->m_Renderer, font->mTexture, nullptr, &font->dstrect);
	SDL_RenderCopy(this->mGame->m_Renderer, title, nullptr, &titleRect);


}
