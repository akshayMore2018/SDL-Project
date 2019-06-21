#pragma once
#include <vector>
#include <unordered_map>
#include "SDL.h"
class View
{
public:
	View(class Game* game);

	virtual void enter();
	virtual void exit();
	virtual void events();
	virtual void update(float deltaTime);
	virtual void render();

	void setScreen(class Screen * screen);

	SDL_Texture* getTexture(const std::string& filename);
	class Game* getGame() const { return mGame; }


protected:
	class Game* mGame;
	class Screen* currentScreen;
	std::unordered_map<std::string, SDL_Texture*> m_Textures;
};