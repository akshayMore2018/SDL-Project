#pragma once
#include <iostream>
#include <unordered_map>
#include "SDL.h"
#include "SDL_ttf.h"
class Font
{
public:
	Font();
	~Font();

	bool load(const std::string& fileName);
	void unLoad();
	SDL_Texture* RenderText(const std::string& text, int pointSize = 30);

private:
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
};