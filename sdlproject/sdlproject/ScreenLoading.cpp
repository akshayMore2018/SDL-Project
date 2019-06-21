#include "ScreenLoading.h"
#include <iostream>
#include "GameView.h"
#include "Game.h"
#include "Font.h"
ScreenLoading::ScreenLoading(short unsigned int ID, GameView * view)
	:Screen(ID), mView(view)
{

}

ScreenLoading::~ScreenLoading()
{
	delete font;
}

int loadMap(void * ptr)
{
	GameView* view = (GameView*)ptr;
	view->init();
	return 0;
}

void ScreenLoading::enter()
{
	angle = 0;
	threadID = SDL_CreateThread(loadMap, "mapLoadingThread", mView);

	if (threadID == NULL) 
	{
		std::cout << "SDL_CreateThread failed: " << SDL_GetError() << std::endl;
	}
	mTicksCount = SDL_GetTicks();
	spinner = mView->getTexture("Assets/gui/spinner.png");
	font = new Font(mView->getGame());
	font->load("Assets/fonts/m5x7/m5x7.ttf");
	font->RenderText("Loading",52);
	font->setFontPosition(512-font->getFontWidth()/2, 420);
	
}

void ScreenLoading::events()
{

}

void ScreenLoading::update(float deltaTime)
{
	float timeElapsed = (SDL_GetTicks() - mTicksCount) / 1000.0f; //to use fake loading if map loaded too fast
	if (mView->gameLoaded && timeElapsed>3.0f)
	{
		mView->setScreen(nullptr);
	}
}

void ScreenLoading::render()
{
	SDL_Rect dstRect = { 512-30,384-30,60,60 };
	SDL_Point center = {30,30};
	angle += 6;
	SDL_RenderCopyEx(mView->getGame()->m_Renderer, spinner, nullptr, &dstRect,angle,&center,SDL_FLIP_NONE);
	SDL_RenderCopy(mView->getGame()->m_Renderer, font->mTexture, nullptr, &font->dstrect);
}

void ScreenLoading::exit()
{
	if (threadID != NULL) {
		SDL_WaitThread(threadID, &threadReturnValue);
		std::cout << "Thread returned value: " << threadReturnValue << std::endl;
	}
}
