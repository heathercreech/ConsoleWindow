#ifndef SCAPPLICATION_H
#define SCAPPLICATION_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include <stdio.h>
#include "scinput.h"
#include "scobject.h"
#include "debug.h"

class ApplicationObject;

//handles initiation and clean up
class Application{
public:
	Application();
	~Application();
	
	int init();
	void handleInput();
	void loop();
	void update();
	void render();
	void stop();
	
	bool canRun();
	void addObject(ApplicationObject*);
	
	ApplicationDebug getDebug();
	void setDebug(bool);
	void log_info(const char*);
	void log_error(const char*);
	
	Input* getInput();
	
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	
private:
	std::vector<ApplicationObject*> objs;
	
	bool can_run = false;
	
	Input input;
	
	ApplicationDebug debug;
	
	SDL_Window* app_window = NULL;
	SDL_Renderer* app_renderer = NULL;
};

#endif