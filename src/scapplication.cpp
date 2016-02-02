#include "scapplication.h"

//takes the Application's renderer to allow the object to render itself

Application::Application(){}


Application::~Application(){
	stop();
}

int Application::init(){

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL_Init failed: %s", SDL_GetError());
		return -1;
	}

	app_window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if(app_window == NULL){
		printf("SDL_CreateWindow failed: %s", SDL_GetError());
		return -1;
	}
	
	app_renderer = SDL_CreateRenderer(app_window, -1, SDL_RENDERER_ACCELERATED);
	if(app_renderer == NULL){
		printf("SDL_CreateRenderer failed: %s", SDL_GetError());
		return -1;
	}
	
	//initialize TTF
	if(TTF_Init() == -1){
		printf("TTF_Init() failed: %s", TTF_GetError());
		return -1;
	}
	
	//allow the app to be ran is initialization was successful
	can_run = true;
	
	debug.setupTag("info", "[INFO]");
	debug.setupTag("error", "[ERROR]");
	return 1;
}

ApplicationDebug Application::getDebug(){
	return debug;
}

void Application::log_info(const char* content){
	debug.log("info", content);
}

void Application::log_error(const char* content){
	debug.log("error", content);
}

void Application::handleInput(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_ESCAPE:
						can_run = false;
						break;
					default:
						input.setKey(e.key.keysym.sym, true);
				}
				break;
			case SDL_KEYUP:
				input.setKey(e.key.keysym.sym, false);
				break;
			case SDL_QUIT:
				can_run = false;
		}
		input.updateEvent(e);
	}
}

void Application::loop(){
	Uint32 MS_PER_UPDATE = 16;
	Uint32 previous_time = SDL_GetTicks();
	Uint32 lag = 0;
	while(canRun()){
	
		Uint32 current_time = SDL_GetTicks();
		Uint32 elapsed_time = current_time - previous_time;
		previous_time = current_time;
		lag += elapsed_time;	
		
		if(lag >= MS_PER_UPDATE){
			handleInput();
			update();
			lag -= MS_PER_UPDATE;
		}
		
		render();
		getInput()->clearDown();
	}
}

void Application::update(){
	for(unsigned int i = 0; i < objs.size(); i++){
		objs[i]->update();
	}
}

void Application::render(){
	SDL_SetRenderDrawColor(app_renderer, 0, 0, 0, 255);
	SDL_RenderClear(getRenderer());
	for(unsigned int i = 0; i < objs.size(); i++){
		objs[i]->render();
	}
	SDL_RenderPresent(getRenderer());
}

void Application::stop(){
	SDL_DestroyRenderer(app_renderer);
	SDL_DestroyWindow(app_window);
	
	TTF_Quit();
	SDL_Quit();
}


SDL_Window* Application::getWindow(){
	return app_window;
}


SDL_Renderer* Application::getRenderer(){
	return app_renderer;
}

Input* Application::getInput(){
	return &input;
}

bool Application::canRun(){
	return can_run;
}

void Application::addObject(ApplicationObject* app_obj){
	objs.push_back(app_obj);
}

void Application::setDebug(bool debug_on){
	debug.setDebug(debug_on);
}