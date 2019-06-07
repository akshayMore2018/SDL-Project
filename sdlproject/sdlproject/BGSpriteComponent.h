#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	void update(float deltaTime);
	void draw(SDL_Renderer* renderer);

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { this->m_ScreenSize = size; }
	void SetScrollSpeed(float speed) { this->m_ScrollSpeed = speed; }
	float GetScrollSpeed() const { return this->m_ScrollSpeed; }


private:
	struct BGTexture
	{
		SDL_Texture* m_Texture;
		Vector2 m_Offset;
	};
	std::vector<BGTexture> m_BGTextures;
	Vector2 m_ScreenSize;
	float m_ScrollSpeed;

};