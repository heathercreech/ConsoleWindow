#ifndef SCOBJECT_H
#define SCOBJECT_H

#include "scapplication.h"
#include "scrender.h"
#include "sclogic.h"

class ObjectRenderer;
class ObjectLogic;
class Application;

//directs all object functions (rendering, logic, etc...)
class ApplicationObject{
public:
	ApplicationObject(Application*, ObjectRenderer*, ObjectLogic*);
	~ApplicationObject(){};
	void update();
	void render();
	
	ObjectLogic* getLogic();

private:
	Application* app;
	ObjectRenderer* obj_renderer;
	ObjectLogic* obj_logic;
};

#endif