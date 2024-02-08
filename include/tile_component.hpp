#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class Tile_component: public Entity
{
    public:
    void update();

};