#include "BGSpriteComponent.h"
#include "Player.h"
#include <iostream>
#include "World.h"
BGSpriteComponent::BGSpriteComponent(Player * owner, int drawOrder)
	:SpriteComponent(owner, drawOrder),
	m_ScrollSpeed(0.0f), mPlayer(owner),speed(0)
{

}

void BGSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);
	for (auto& bg : this->m_BGTextures)
	{
		if (bg.m_Offset.x < -m_ScreenSize.x)
		{
			bg.m_Offset.x = (m_BGTextures.size() - 1) * m_ScreenSize.x - 2;
		}
		else if (bg.m_Offset.x > m_ScreenSize.x)
		{
			bg.m_Offset.x = (m_BGTextures.size() - 1) * m_ScreenSize.x - 2;
			bg.m_Offset.x = -bg.m_Offset.x;
		}

		if ((World::camera.x == 0) || (World::camera.x == World::mapWidth - World::camera.w))
		{
			speed = 0;
		}
		else
		{

			speed = m_ScrollSpeed * -mPlayer->xsp*0.2f;
		}
		bg.m_Offset.x += speed * deltaTime;
	}
}

void BGSpriteComponent::draw(SDL_Renderer * renderer)
{
	for (auto& bg : m_BGTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(m_ScreenSize.x);
		r.h = static_cast<int>(m_ScreenSize.y);
		
		r.x = static_cast<int>(bg.m_Offset.x);
		r.y = static_cast<int>(bg.m_Offset.y);

		// Draw this background
		SDL_RenderCopy(renderer,
			bg.m_Texture,
			nullptr,
			&r
		);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.m_Texture = tex;
		// Each texture is screen width in offset
		temp.m_Offset.x = count * m_ScreenSize.x;
		temp.m_Offset.y = 0;
		m_BGTextures.emplace_back(temp);
		count++;
	}
}
