#include "scinput.h"
#include <stdio.h>

Input::Input(){

	//DIRECTIONAL KEYS
	key_set[SDLK_UP] = false;
	key_set[SDLK_LEFT] = false;
	key_set[SDLK_DOWN] = false;
	key_set[SDLK_RIGHT] = false;
	
	key_set[SDLK_w] = false;
	key_set[SDLK_a] = false;
	key_set[SDLK_s] = false;
	key_set[SDLK_d] = false;
	
	//MISC KEYS
	key_set[SDLK_ESCAPE] = false;
}

bool Input::hasEvent(Uint32 key){
	std::map<Uint32, SDL_Event>::iterator iter = cur_events.find(key);
	if(iter != cur_events.end()){
		return true;
	}
	return false;
}

void Input::updateEvent(SDL_Event e){
	cur_events[e.type] = e;
}

void Input::setKey(SDL_Keycode key, bool is_down){
	if((is_down == true && key_set[key] == true) || is_down == false){
		key_down[key] = false;
	}else{
		key_down[key] = true;
	}
	
	if(is_down == false && key_set[key] == true){
		key_up[key] = true;
	}
	
	key_set[key] = is_down;
}


bool Input::getKey(SDL_Keycode key){
	return key_set[key];
}


bool Input::getKeyDown(SDL_Keycode key){
	return key_down[key];
}


bool Input::getKeyUp(SDL_Keycode key){
	return key_up[key];
}


//returns true if any key is currently pressed
KeyInfo Input::anyKey(){
	KeyInfo key_info;
	
	for(std::map<SDL_Keycode, bool>::iterator it = key_set.begin(); it != key_set.end(); it++){
		if(key_set[it->first]){
			key_info.pressed = true;
			key_info.key = it->first;
			return key_info;
		}
	}
	
	return key_info;
}


//returns true when a key is pressed down (only once)
KeyInfo Input::anyKeyDown(){
	KeyInfo key_info;
	
	for(std::map<SDL_Keycode, bool>::iterator it = key_down.begin(); it != key_down.end(); it++){
		if(key_down[it->first]){
			key_info.pressed = true;
			key_info.key = it->first;
			return key_info;
		}
	}
	
	return key_info;
}


//returns true when a key is unpressed (only once)
KeyInfo Input::anyKeyUp(){
	KeyInfo key_info;
	
	for(std::map<SDL_Keycode, bool>::iterator it = key_up.begin(); it != key_up.end(); it++){
		if(key_up[it->first]){
			key_info.pressed = true;
			key_info.key = it->first;
			return key_info;
		}
	}
	
	return key_info;
}


void Input::clearDown(){
	for(const auto &pair : key_down){
		key_down[pair.first] = false;
	}
	
	for(const auto &pair : key_up){
		key_up[pair.first] = false;
	}
	
	cur_events.clear();
}

//checks if an event of event_type has occured
MouseInfo Input::getMouseButtonEvent(Uint32 event_type, Uint32 mouse_button){
	if(hasEvent(event_type)){
		SDL_MouseButtonEvent mouse_event = cur_events[event_type].button;
		
		if(mouse_event.button == mouse_button){
			return MouseInfo(true, mouse_event.x, mouse_event.y, mouse_event.clicks, mouse_event.windowID, mouse_event.timestamp);
		}
	}
	return MouseInfo();
}

MouseInfo Input::getMouseButtonDown(Uint32 mouse_button){
	return getMouseButtonEvent(SDL_MOUSEBUTTONDOWN, mouse_button);
}

MouseInfo Input::getMouseButtonUp(Uint32 mouse_button){
	return getMouseButtonEvent(SDL_MOUSEBUTTONUP, mouse_button);
}