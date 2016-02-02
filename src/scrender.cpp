#include "scrender.h"

/*START OBJECTRENDERER*/

ObjectRenderer::ObjectRenderer(SDL_Renderer* renderer){
	app_renderer = renderer;
}

/*END OBJECTRENDERER*/



/*START SQUARERENDERER*/

SquareRenderer::SquareRenderer(SDL_Renderer* ren, SDL_Rect* r, SDL_Color* c) : ObjectRenderer(ren){
	rect = r;
	color = c;
}



void SquareRenderer::render(){
	SDL_SetRenderDrawColor(app_renderer, color->r, color->g, color->b, color->a);
	SDL_RenderFillRect(app_renderer, rect);
}



SDL_Rect* SquareRenderer::getRect(){
	return rect;
}

/*END SQUARERENDERER*/



/*START FONTRENDERER*/

FontRenderer::FontRenderer(SDL_Renderer* app_renderer) : ObjectRenderer(app_renderer){

	defaultSetup();
	font_surface = TTF_RenderText_Solid(font, "This is sample text.", color);
	font_texture = SDL_CreateTextureFromSurface(app_renderer, font_surface);
}


FontRenderer::FontRenderer(SDL_Renderer* app_renderer, std::string t) : ObjectRenderer(app_renderer){
	
	defaultSetup();

	font_surface = TTF_RenderText_Solid(font, t.c_str(), color);
	font_texture = SDL_CreateTextureFromSurface(app_renderer, font_surface);
}


FontRenderer::FontRenderer(SDL_Renderer* app_renderer, std::string* t) : ObjectRenderer(app_renderer){
	
	defaultSetup();
	
	text = t;
	font_surface = TTF_RenderText_Solid(font, text->c_str(), color);
	font_texture = SDL_CreateTextureFromSurface(app_renderer, font_surface);
}


FontRenderer::FontRenderer(SDL_Renderer* app_renderer, SDL_Rect* font_rect, SDL_Color font_color, char* font_name, int size) : ObjectRenderer(app_renderer){

	font = TTF_OpenFont(font_name, size);

	setColor(font_color);

	font_surface = TTF_RenderText_Solid(font, "This is sample text.", color);
	font_texture = SDL_CreateTextureFromSurface(app_renderer, font_surface);
	
	setRect(font_rect);
}


FontRenderer::~FontRenderer(){
	SDL_FreeSurface(font_surface);
	TTF_CloseFont(font);
}


void FontRenderer::defaultSetup(){
	setupFont("arial.ttf", 12);
	color = {255, 255, 255};
}


void FontRenderer::setupFont(char* name, int size){
	font_size = size;
	font_name = name;
	font = TTF_OpenFont(name, font_size);
}


void FontRenderer::setRect(SDL_Rect* new_rect){
	rect = new_rect;
	rect->w = font_surface->w;
	rect->h = font_surface->h;
}


void FontRenderer::setColor(SDL_Color new_color){
	color = new_color;
}


//get the text
std::string FontRenderer::getText(){
	return *text;
}


//get the font_surface
SDL_Surface* FontRenderer::getSurface(){
	return font_surface;
}


void FontRenderer::render(){
	SDL_RenderCopy(app_renderer, font_texture, NULL, rect);
}

/*END FONTRENDERER*/