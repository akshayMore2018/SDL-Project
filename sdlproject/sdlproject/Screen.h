#pragma once
class Screen
{
public:
	enum
	{
		LOAD,
		PAUSE,
	};
	Screen(short unsigned int screenID) :ID(screenID){};
	virtual ~Screen() {};

	virtual void enter()=0;

	virtual void events()=0;
	virtual void update(float deltaTime)=0;
	virtual void render()=0;

	virtual void exit()=0;

protected:
	short unsigned int ID;
};