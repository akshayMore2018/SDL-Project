#include "ScreenLoading.h"
#include <iostream>
#include "GameView.h"
#include "Game.h"
ScreenLoading::ScreenLoading(short unsigned int ID, GameView * view)
	:Screen(ID), mView(view)
{
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

	spinner = mView->getTexture("Assets/spinner.png");
}

void ScreenLoading::events()
{

}

void ScreenLoading::update(float deltaTime)
{
	if (mView->gameLoaded)
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
}

void ScreenLoading::exit()
{
	if (threadID != NULL) {
		SDL_WaitThread(threadID, &threadReturnValue);
		std::cout << "Thread returned value: " << threadReturnValue << std::endl;
	}
}
