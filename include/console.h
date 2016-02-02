#ifndef CONSOLE_H
#define CONSOLE_H

#include "scapplication.h"
#include <deque>
#include <string>
#include <cctype>

//contains the consoles starting position
struct ConsolePosition{
	int x = 0;
	int y = 0;
};


//consoles renderer, in charge of rendering all lines of the console
class ConsoleRenderer : public ObjectRenderer{
public:
	ConsoleRenderer(Application*, ConsolePosition);
	~ConsoleRenderer();
	
	void updatePosition(int, int);
	void addLine(std::string);
	
	void updateInputLine(std::string);
	
	void render();
private:
	Application* app;
	unsigned int max_lines;
	unsigned int current_lines;
	std::deque<SDL_Rect*> line_rects;
	std::deque<FontRenderer*> console_lines;
	
	
	SDL_Rect* input_line_rect;
	FontRenderer* input_line_renderer; //the line we will be typing on
	
	ConsolePosition console_pos;
	
	void setupLines();
	void removeFront();
};


//consoles logic, in charge of adding lines to the console and input
class ConsoleLogic : public ObjectLogic{
public:
	ConsoleLogic(Application*, ConsoleRenderer*);
	
	void update();
	
private:
	ConsoleRenderer* renderer;
	
	std::string current_input;
	
	void getRect(); //hide parent class method to prevent null pointer exception, use ConsoleRenderer::updatePosition(int, int) to change the console's position
	void setPosition(int, int); //hide parent class method to prevent null pointer exception, use ConsoleRenderer::updatePosition(int, int) to change the console's position
};

#endif