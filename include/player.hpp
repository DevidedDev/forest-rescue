#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>

#include "entity.hpp"
#include "player.hpp"

class Player: public Entity
{

private:
//player textures
    //std::map<string, SDL_Texture*> textures {};
    //water amount
    float max_water;
    float cur_water;
    //heatlh
    float max_hp;
    float cur_hp;
    

public:
    Player(Vector2f p_pos, SDL_Texture* p_tex);
    
};

