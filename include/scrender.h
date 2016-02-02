#ifndef SCRENDER_H
#define SCRENDER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
#include "scapplication.h"
#include <cstdio>


class Application;


class ObjectRenderer{
public:
	ObjectRenderer(){};
	ObjectRenderer(SDL_Renderer*);
	virtual ~ObjectRenderer(){};
	virtual void render(){};
	SDL_Renderer* app_renderer;
};

//wrapper for SDL_Texture
class SquareRenderer : public ObjectRenderer{
public:
	SquareRenderer(SDL_Renderer*, SDL_Rect*, SDL_Color*);
	~SquareRenderer(){};
	SDL_Rect* getRect();
	void render();
private:
	SDL_Color* color;
	SDL_Rect* rect;
};


class FontRenderer : public ObjectRenderer{
public:
	FontRenderer(SDL_Renderer*); //default initializer
	FontRenderer(SDL_Renderer*, std::string); //text initializer
	FontRenderer(SDL_Renderer*, std::string*); //text pointer initializer
	FontRenderer(SDL_Renderer*, SDL_Rect*, SDL_Color, char*, int);
	~FontRenderer(); //free surface and close font
	
	void setRect(SDL_Rect*);
	void setColor(SDL_Color);
	
	
	std::string getText();
	SDL_Surface* getSurface();
	
	void render();
private:
	TTF_Font *font;
	SDL_Color color;
	SDL_Rect* rect;
	SDL_Surface* font_surface;
	SDL_Texture* font_texture;
	
	std::string* text;
	
	int font_size;
	char* font_name;
	
	void defaultSetup();
	void setupFont(char*, int);
};

#endif