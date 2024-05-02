#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "render_window.hpp"

struct Textures{
    SDL_Texture* player;
    SDL_Texture* enemy;
    SDL_Texture* tribesmen;

    SDL_Texture* grass;
    SDL_Texture* water;
    SDL_Texture* trees;
    SDL_Texture* fire;
    SDL_Texture* village;
    SDL_Texture* forest_bg;
    Textures(RenderWindow& p_window);

};




struct Colors{
    static SDL_Color white, black, gray;
    
};