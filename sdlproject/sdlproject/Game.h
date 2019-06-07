#pragma once
#include "SDL.h"
#include <vector>
#include <unordered_map>
class Game
{
public:
	Game();
	~Game();

	bool initialize();

	void run();

	void stop();
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

private:

	SDL_Texture* getTexture(const std::string& filename);

	void loadData();
	void unloadData();
	void events();
	void update();
	void render();

	std::unordered_map<std::string, SDL_Texture*> m_Textures;
	std::vector<class SpriteComponent*> m_Sprites;
	
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	bool m_IsRunning;
	Uint32 mTicksCount;
	bool m_UpdatingActors;
	std::vector<Actor*> m_PendingActors;
	std::vector<Actor*> m_Actors;
};