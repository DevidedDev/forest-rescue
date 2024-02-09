#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.hpp"
 

class Keyboard{
private:
    bool KEYS[322];
public:
    Keyboard();
    void getKey(SDL_Event& event, bool key_down);
    

};

class Mouse{
private:
public:
    void getBtn(SDL_Event& event);
};

class Input{
private:
    SDL_Event event;
    Keyboard keyboard;
    Mouse mouse;
public:
    void getInput();
};
   
