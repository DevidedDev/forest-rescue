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
    Textures(RenderWindow& p_window);

};