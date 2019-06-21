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

	bg = mView->getTexture("Assets/map/metaTile.png");
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
	SDL_Rect rect = { 512,384,100,100 };
	angle += 1;
	SDL_RenderCopyEx(mView->getGame()->m_Renderer, bg, nullptr, &rect,angle,nullptr,SDL_FLIP_NONE);
}

void ScreenLoading::exit()
{
	if (threadID != NULL) {
		SDL_WaitThread(threadID, &threadReturnValue);
		std::cout << "Thread returned value: " << threadReturnValue << std::endl;
	}
}
