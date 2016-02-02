#ifndef SCINPUT_H
#define SCINPUT_H

#include <SDL.h>
#include <map>

//contains information regarding mouse input events, returned with set = false if an event has not occured
struct MouseInfo{
	bool set;
	Sint32 x;
	Sint32 y;
	Uint8 clicks;
	Uint32 window_id;
	Uint32 timestamp;
	MouseInfo(bool set, Sint32 x, Sint32 y, Uint8 clicks, Uint32 window_id, Uint32 timestamp){
		this->set = set;
		this->x = x;
		this->y = y;
		this->clicks = clicks;
		this->window_id = window_id;
		this->timestamp = timestamp;
	}
	
	MouseInfo(){set = false;} //default constructor, used for determining if an event has occured
};


//contains information about the key that is pressed (for use with the anyKey functions)
struct KeyInfo{
	bool pressed = false;
	SDL_Keycode key;
};

//will handle key states and let ApplicationObjects react to inputs
class Input{
public:
	Input();
	bool getKey(SDL_Keycode);
	bool getKeyDown(SDL_Keycode);
	bool getKeyUp(SDL_Keycode);
	
	KeyInfo anyKey();
	KeyInfo anyKeyDown();
	KeyInfo anyKeyUp();
	
	MouseInfo getMouseButtonEvent(Uint32, Uint32);
	MouseInfo getMouseButtonDown(Uint32);
	MouseInfo getMouseButtonUp(Uint32);
	
	void setKey(SDL_Keycode, bool);
	void clearDown();
	
	bool hasEvent(Uint32);
	void updateEvent(SDL_Event);
private:
	std::map<SDL_Keycode, bool> key_down;
	std::map<SDL_Keycode, bool> key_up;
	std::map<SDL_Keycode, bool> key_set;
	
	std::map<Uint32, SDL_Event> cur_events;
};

#endif