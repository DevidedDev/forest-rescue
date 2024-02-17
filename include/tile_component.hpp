#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"

class TileComp
{
private:
    Entity tree;
    Entity grass;
public:
   
    TileComp(const Vector2f& p_pos);
    TileComp();
    void update();
    void render();
    Entity* getTree();
    Entity* getGrass();
    
};