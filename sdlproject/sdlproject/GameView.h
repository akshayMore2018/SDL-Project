#pragma once
#include "View.h"

class GameView : public View
{

	
public:

	GameView(class Game * game);

	 void init();
	 void enter();
	 void exit();
	 void events();
	 void update(float deltaTime);
	 void render();

	//helper functions
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);

	void addCollider(class CollisionComponent* collider);
	void removeCollider(class CollisionComponent* collider);

	void addRay(class RayComponent* ray);
	void removeRay(class RayComponent* ray);

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	//getters
   
	std::vector<class Actor*>& getActors() { return m_Actors; }
	class World* getWorld() const { return mWorld; }
	bool gameLoaded;
private:
	std::vector<class SpriteComponent*> m_Sprites;
	std::vector<class CollisionComponent*> m_Colliders;
	std::vector<class RayComponent*> m_Rays;
	std::vector<Actor*> m_PendingActors;
	std::vector<Actor*> m_Actors;
	bool m_UpdatingActors;
	class World* mWorld;
};
