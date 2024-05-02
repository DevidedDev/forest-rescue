#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"
#include "fire.hpp"

class TileComp
{
private:
    Entity tree;
    Entity grass;
    Fire fire;
    bool isBurned;
    bool isBurning;
    int lastTimeBurned;

    

public:
    static int burnedTilesNum;
    TileComp(const Vector2f& p_pos);
    TileComp();
    TileComp( TileComp& tile_comp);
    void update();
    void render();
    Entity* getTree();
    Entity* getGrass();
    void startBurning();
    bool getIsBurning();
    bool getIsBurned();
    Fire& getFire();
    int getLastTimeBurned();
    void renderGrass();
    void renderTree();
    void renderFire();
    static void resetBurnedTilesNum();
    static  int getBurnedTilesNum();
    
};