#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "tile_component.hpp"
#include "math.hpp"

class Level{
private:
    Dimension dimension;
    std::vector<std::vector<TileComp*>> tiles;
public:
    Level();
    ~Level();
    Dimension getDimension();
    TileComp getTile(int x, int y);
    void update();
    void render();
};