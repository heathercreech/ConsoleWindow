#include "scobject.h"

ApplicationObject::ApplicationObject(Application* application, ObjectRenderer* renderer, ObjectLogic* logic){
	app = application;
	obj_renderer = renderer;
	obj_logic = logic;
}

void ApplicationObject::update(){
	obj_logic->update();
}

void ApplicationObject::render(){
	if(obj_renderer != NULL){
		obj_renderer->render();
	}
}

ObjectLogic* ApplicationObject::getLogic(){
	return obj_logic;
}