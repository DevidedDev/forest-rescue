#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "math.hpp"

class Entity{
private:
    Vector2f pos; //changable x & y pos
        
    SDL_Rect currentFrame; // probably constatnt position and width?? 
    SDL_Texture* tex; // texture

public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex);
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTex();
    Vector2f& getPos(){
        return pos;
    };
    

};