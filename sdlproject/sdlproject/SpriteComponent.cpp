#include "SpriteComponent.h"
#include "Actor.h"
#include "View.h"
#include <iostream>
#include "World.h"

SpriteComponent::SpriteComponent(Actor * owner, int drawOrder)
	:Component(owner),
	m_Texture(nullptr),
	m_DrawOrder(drawOrder),
	m_TextureWidth(0),
	m_TextureHeight(0)
{
	m_Owner->getView()->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	this->m_Owner->getView()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer * renderer)
{
	if (this->m_Texture)
	{
		
		SDL_Rect rect;

		rect.w = static_cast<int>(this->m_TextureWidth*this->m_Owner->getScale());
		rect.h = static_cast<int>(this->m_TextureHeight*this->m_Owner->getScale());

		rect.x = static_cast<int>(this->m_Owner->getPosition().x - rect.w / 2 - World::camera.x);
		rect.y = static_cast<int>(this->m_Owner->getPosition().y - rect.h / 2 - World::camera.y);

		SDL_RenderCopyEx(renderer,
			this->m_Texture,
			nullptr,
			&rect,
			(this->m_Owner->getRotation())*180/3.1415926535f,
			nullptr,
			SDL_FLIP_NONE);


	}
}

void SpriteComponent::setTexture(SDL_Texture * texture)
{
	this->m_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &this->m_TextureWidth, &this->m_TextureHeight);
}

