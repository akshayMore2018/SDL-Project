#pragma once
#include <iostream>
#include <unordered_map>
#include "SDL.h"
#include "SDL_ttf.h"
class Font
{
public:
	Font(class Game* game);
	~Font();

	bool load(const std::string& fileName);
	void unLoad();
	void RenderText(const std::string& text, int pointSize = 30);
	void setFontPosition(float x, float y);
	SDL_Texture* mTexture;
	SDL_Rect dstrect;

	const int getFontWidth() const { return dstrect.w; }
	const int getFontHeight() const { return dstrect.h; }
private:
	std::unordered_map<int, TTF_Font*> mFontData;
	class Game* mGame;
	
};