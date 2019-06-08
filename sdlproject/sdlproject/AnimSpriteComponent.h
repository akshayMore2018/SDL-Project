#pragma once
#include "SpriteComponent.h"
#include <iostream>
#include <map>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int draworder = 100);
	~AnimSpriteComponent();
	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);
	void setAnimation(const std::string& ID,int loop);
	void addAnimation(const std::string& ID, const std::string & filename, float frameX, float frameY, float frameWidth, float frameHeight, float frameRate, float frameCount);
private:
	void setTextureRect(float x, float y, float w, float h);
	float mCurrFrame;
	float mFrameRate;
	int mTotalFrames;
	int mTotalCycles;
	int mCurrentCycle;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	SDL_Point center;
	std::map<std::string, class AnimationData*> animDataSet;
	std::string currentAnimID;
	bool animComplete;
};

class AnimationData
{
public:
	AnimationData(const std::string& name,float x, float y, float width, float height, float rate, float frames)
	:spritefile(name),x(x),y(y),frameWidth(width),frameHeight(height),frameRate(rate),frameCount(frames)
	{}

	std::string spritefile;
	float x;
	float y;
	float frameWidth;
	float frameHeight;
	float frameRate;
	float frameCount;
};