#include "AnimSpriteComponent.h"
#include "Actor.h"
#include "GameView.h"
#include "World.h"

AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int draworder)
	:SpriteComponent(owner,draworder),
	mCurrFrame(0),
	mFrameRate(0),
	initialFrameRate(0),
	mTotalFrames(0),
	mTotalCycles(-1),
	mCurrentCycle(0),
	srcRect{0,0,0,0},
	dstRect{0,0,0,0},
	center{0,0}
{
}

AnimSpriteComponent::~AnimSpriteComponent()
{
	for (auto i : this->animDataSet)
	{
		delete i.second;
	}
	this->animDataSet.clear();
}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	if (this->animComplete)
		return;

	if (this->m_Texture)
	{
		this->mCurrFrame += this->mFrameRate * deltaTime;

		if (this->mCurrFrame > this->mTotalFrames)
		{
			
			this->mCurrFrame -= this->mTotalFrames;
			mCurrentCycle++;
		}
		if (mCurrentCycle == mTotalCycles)
		{
			mCurrFrame = this->mTotalFrames - 1;
			this->animComplete = true;
			this->m_Owner->onAnimCompleteEvent(this->currentAnimID);
		}
		this->m_Owner->currentAnimFrame(this->currentAnimID,(int)mCurrFrame);
		srcRect.x = (int)mCurrFrame*this->srcRect.w;
	}
}

void AnimSpriteComponent::draw(SDL_Renderer * renderer)
{
	if (this->m_Texture)
	{

		this->dstRect.x = this->m_Owner->getPosition().x - this->dstRect.w / 2 - World::camera.x;
		this->dstRect.y = this->m_Owner->getPosition().y - this->dstRect.h / 2 - World::camera.y;
		SDL_RenderCopyEx(
			renderer,
			this->m_Texture,
			&srcRect,
			&dstRect,
			this->m_Owner->getRotation()*(180/3.1451),
			&center,
			this->m_Owner->flipStateX
			);
			
	}

}

void AnimSpriteComponent::setAnimation(const std::string & ID, int loop)
{
	AnimationData* data = this->animDataSet[ID];
	setTexture(this->m_Owner->getView()->getTexture(data->spritefile));
	this->mTotalFrames = data->frameCount;
	this->mFrameRate = data->frameRate;
	this->setTextureRect(data->x, data->y, data->frameWidth, data->frameHeight);
	this->mTotalCycles = loop;
	this->currentAnimID = ID;
	this->animComplete = false;
	this->mCurrentCycle = 0;
	this->mCurrFrame = 0;
	this->initialFrameRate = this->mFrameRate;
}


void AnimSpriteComponent::addAnimation(const std::string & ID,const std::string & filename, float frameX, float frameY, float frameWidth, float frameHeight, float frameRate, float frameCount)
{
	animDataSet[ID] = new AnimationData(filename, frameX, frameY, frameWidth, frameHeight, frameRate, frameCount);
}

void AnimSpriteComponent::setFrameRate(float rate)
{
	this->mFrameRate = rate;
}

void AnimSpriteComponent::setTextureRect(float x, float y, float w, float h)
{
	this->srcRect.x = static_cast<int>(x);
	this->srcRect.y = static_cast<int>(y);
	this->srcRect.w = static_cast<int>(w);
	this->srcRect.h = static_cast<int>(h);

	this->dstRect.w = this->srcRect.w*this->m_Owner->getScale();
	this->dstRect.h = this->srcRect.h*this->m_Owner->getScale();
	this->dstRect.x = this->m_Owner->getPosition().x - this->dstRect.w / 2;
	this->dstRect.y = this->m_Owner->getPosition().y - this->dstRect.h / 2;

	this->center.x = static_cast<int>((w) / 2);
	this->center.y = static_cast<int>((h) / 2);
}


