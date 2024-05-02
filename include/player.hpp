#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>

#include "being.hpp"
#include "math.hpp"

class Player: public Being
{
private:
    //water amount
    float max_water;
    float cur_water;
    //heatlh
    float max_hp;
    float cur_hp;

    Vector2f velocity;
    
public:
    Player( SDL_Texture* p_tex);
    };