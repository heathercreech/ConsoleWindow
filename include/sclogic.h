#ifndef SCLOGIC_H
#define SCLOGIC_H

#include <SDL.h>
#include "scapplication.h"

class Application;

class ObjectLogic{
public:
	ObjectLogic(Application*, SDL_Rect*);
	virtual void update();
	void setPosition(int, int);
	SDL_Rect getRect();

	Application* app;
	
private:
	SDL_Rect* rect;
};

#endif