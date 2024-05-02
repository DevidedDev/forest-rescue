#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entity.hpp"
#include "timer.hpp"

class Fire: public Entity{
private:
    short fireStage;
   // int burnTime; // HOW LONG BEFORE TREE FULLY BURNS
    Timer timer; // -> only for animation 
    int burnStart;
    int lastSpread;
   // bool isSpread;
public:
    Fire(Vector2f p_pos);
    Fire(const Fire& p_fire);
    Fire();
    void updateFrame();
    bool spread();
    void update();
    bool destroyTile();
    bool putOut();
    void setBurnStart();
    int getBurnStart();
    int getLastSpread();
    void setLastSpread();
};