#pragma once
#include <vector>
#include <unordered_map>
#include "SDL.h"
class View
{
public:
	View(class Game* game);

	virtual void loadData();
	virtual void unloadData();
	virtual void events();
	virtual void update(float deltaTime);
	virtual void render();

protected:
	class Game* mGame;
};