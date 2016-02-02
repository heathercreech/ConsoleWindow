#include "sclogic.h"

ObjectLogic::ObjectLogic(Application* application, SDL_Rect* r){
	rect = r;
	app = application;
}

void ObjectLogic::update(){
}

void ObjectLogic::setPosition(int x, int y){
	rect->x = x;
	rect->y = y;
}

SDL_Rect ObjectLogic::getRect(){
	return *rect;
}