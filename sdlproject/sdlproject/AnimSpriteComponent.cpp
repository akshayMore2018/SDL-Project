#include "AnimSpriteComponent.h"
#include "Actor.h"
#include "Game.h"
AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int draworder)
	:SpriteComponent(owner,draworder),
	mCurrFrame(0),
	mFrameRate(0),
	mTotalFrames(0),
	srcRect{0,0,0,0},
	dstRect{0,0,0,0},
	center{0,0}
{
}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);

	if (this->m_Texture)
	{
		this->mCurrFrame += this->mFrameRate * deltaTime;

		while (this->mCurrFrame > this->mTotalFrames)
		{
			this->mCurrFrame -= this->mTotalFrames;
		}

		srcRect.x = (int)mCurrFrame*this->srcRect.w;

	}
}

void AnimSpriteComponent::draw(SDL_Renderer * renderer)
{
	if (this->m_Texture)
	{
		SDL_RenderCopyEx(
			renderer,
			this->m_Texture,
			&srcRect,
			&dstRect,
			this->m_Owner->getRotation()*(180/3.1451),
			&center,
			SDL_FLIP_NONE
			);
		
			
	}
}

void AnimSpriteComponent::setAnimation(const std::string & ID, int loop)
{
	AnimationData* data = this->animDataSet[ID];
	setTexture(this->m_Owner->getGame()->getTexture(data->spritefile));
	this->mTotalFrames = data->frameCount;
	this->mFrameRate = data->frameRate;
	this->setTextureRect(data->x, data->y, data->frameWidth, data->frameHeight);
}


void AnimSpriteComponent::addAnimation(const std::string & ID,const std::string & filename, float frameX, float frameY, float frameWidth, float frameHeight, float frameRate, float frameCount)
{
	animDataSet[ID] = new AnimationData(filename, frameX, frameY, frameWidth, frameHeight, frameRate, frameCount);
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

