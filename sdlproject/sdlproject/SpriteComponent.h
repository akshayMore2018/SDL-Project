#pragma once
#include "Component.h"
#include "SDL.h"
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void draw(SDL_Renderer* renderer);
	virtual void setTexture(SDL_Texture* texture);


	inline int getDrawOrder()const;
	inline int getTextureHeight()const;
	inline int getTextureWidth()const;

protected:
	SDL_Texture* m_Texture;
	int m_DrawOrder;
	int m_TextureWidth;
	int m_TextureHeight;
};

int SpriteComponent::getDrawOrder() const
{
	return m_DrawOrder;
}

int SpriteComponent::getTextureHeight() const
{
	return m_TextureHeight;
}

int SpriteComponent::getTextureWidth() const
{
	return m_TextureWidth;
}
