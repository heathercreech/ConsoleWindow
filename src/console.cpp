#include "console.h"


/*BEGIN CONSOLE RENDERER*/


ConsoleRenderer::ConsoleRenderer(Application* application, ConsolePosition c_pos) : ObjectRenderer(application->getRenderer()){
	app = application;
	
	max_lines = 33;
	current_lines = 0;
	
	console_pos = c_pos;
	
	setupLines();
}


//deallocate dynamic variables in the deques
ConsoleRenderer::~ConsoleRenderer(){
	while(!console_lines.empty()){
		removeFront();
	}
	
	delete input_line_renderer;
	delete input_line_rect;
}

//setup line positions and rendering
void ConsoleRenderer::setupLines(){

	//create the rects and the renderers
	for(unsigned int i = 0; i < max_lines; i++){
		
		FontRenderer* f_ren = new FontRenderer(app->getRenderer(), " ");
		SDL_Rect* f_rect = new SDL_Rect();
		
		f_rect->x = console_pos.x; f_rect->y = console_pos.y + (f_ren->getSurface()->h * i);
		line_rects.push_back(f_rect);
		
		f_ren->setRect(line_rects.back());
		
		console_lines.push_back(f_ren);
	}
	
	//create the rect and renderer for the input line
	input_line_renderer = new FontRenderer(app->getRenderer(), " ");
	input_line_rect = new SDL_Rect();
	input_line_rect->x = console_pos.x;
	input_line_rect->y = console_pos.y + (input_line_renderer->getSurface()->h * max_lines);
	
	input_line_renderer->setRect(input_line_rect);
	
}


//add a line to the console, clear an old one if needed
void ConsoleRenderer::addLine(std::string text){
	removeFront();
	
	for(unsigned int i = 0; i < line_rects.size(); i++){
		line_rects[i]->y = console_lines[i]->getSurface()->h * i;
	}
	
	FontRenderer* f_ren = new FontRenderer(app->getRenderer(), text);
	
	SDL_Rect* f_rect = new SDL_Rect();
	f_rect->x = console_pos.x; f_rect->y  = console_pos.y  + (f_ren->getSurface()->h * (max_lines-1));
	f_ren->setRect(f_rect);
	
	console_lines.push_back(f_ren);
	line_rects.push_back(f_rect);
}


//update the input line text
void ConsoleRenderer::updateInputLine(std::string in){
	delete input_line_renderer;
	delete input_line_rect;
	
	input_line_renderer = new FontRenderer(app->getRenderer(), in);
	input_line_rect = new SDL_Rect();
	input_line_rect->x = console_pos.x; input_line_rect->y = console_pos.y + (input_line_renderer->getSurface()->h * max_lines);
	
	input_line_renderer->setRect(input_line_rect);
}


//removes and deallocates the front variables of the deques
void ConsoleRenderer::removeFront(){
	FontRenderer* ren_temp = console_lines.front();
	SDL_Rect* rect_temp = line_rects.front();

	console_lines.pop_front();
	line_rects.pop_front();
	
	delete ren_temp;
	delete rect_temp;
}


//render all the lines
void ConsoleRenderer::render(){

	for(unsigned int i = 0; i < console_lines.size(); i++){
		FontRenderer* line_holder = console_lines.front();
		line_holder->render();
		console_lines.pop_front();
		console_lines.push_back(line_holder);
	}

	input_line_renderer->render();
}


/*END CONSOLE RENDERER*/

/*BEGIN CONSOLE LOGIC*/


ConsoleLogic::ConsoleLogic(Application* application, ConsoleRenderer* console_renderer) : ObjectLogic(application, NULL){
	renderer = console_renderer;
}


//get input and update console lines
void ConsoleLogic::update(){
	
	KeyInfo key_info = app->getInput()->anyKeyDown();
	if(key_info.pressed && key_info.key != SDLK_RETURN && key_info.key != SDLK_BACKSPACE){
		
		std::string new_input = SDL_GetKeyName(key_info.key);
		
		if(new_input.length() == 1){
			if(app->getInput()->getKey(SDLK_LSHIFT) || app->getInput()->getKey(SDLK_RSHIFT)){
				current_input += new_input;
			}else{
				current_input += tolower(new_input.c_str()[0]);
			}
			renderer->updateInputLine(current_input);
		}else if(key_info.key == SDLK_SPACE){
			current_input += " ";
			renderer->updateInputLine(current_input);
		}
	}else if(key_info.key == SDLK_RETURN){
		if(current_input.length() != 0){
			renderer->addLine(current_input);
			current_input = "";
			renderer->updateInputLine(" ");
		}
	}else if(app->getInput()->getKey(SDLK_BACKSPACE)){
		if(current_input.length() != 0){
			current_input.pop_back();
			
			if(current_input.length() != 0){
				renderer->updateInputLine(current_input);
			}else{
				renderer->updateInputLine(" ");
			}
		}
	}
}