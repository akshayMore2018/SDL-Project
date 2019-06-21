#include "Font.h"
#include "Game.h"

Font::Font(Game * game):mGame(game)
{
}

Font::~Font()
{
	unLoad();
	SDL_DestroyTexture(mTexture);
}

bool Font::load(const std::string & fileName)
{
	std::vector<int> fontSizes = {
		8,9,10,11,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,
		42,44,46,48,52,56,60,64,68,72
	};


	for (auto& size : fontSizes)
	{
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (font == nullptr)
		{
			SDL_Log("Failed to load font in size %d", size);
			return false;
		}

		mFontData.emplace(size, font);
	}

	return true;
}

void Font::unLoad()
{
	for (auto font : mFontData)
	{
		TTF_CloseFont(font.second);
	}
	mFontData.clear();
}

void Font::RenderText(const std::string & text, int pointSize)
{
	mTexture = nullptr;
	// Convert to SDL_Color
	SDL_Color sdlColor;
	sdlColor.r = 255;
	sdlColor.g = 255;
	sdlColor.b = 255;
	sdlColor.a = 255;


	auto iter = mFontData.find(pointSize);
	if (iter != mFontData.end())
	{
		TTF_Font* font = iter->second;
		SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
	
		if (surf != nullptr)
		{
			mTexture = SDL_CreateTextureFromSurface(this->mGame->m_Renderer, surf);
			SDL_FreeSurface(surf);
			dstrect.x = 0;
			dstrect.y = 0;
			SDL_QueryTexture(mTexture, NULL, NULL, &dstrect.w, &dstrect.h);
		}
	
	}
	else
	{
		SDL_Log("Point size %d is unsupported", pointSize);
	}
}

void Font::setFontPosition(float x, float y)
{
	dstrect.x = x;
	dstrect.y = y;
}
