#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>

#include "entity.hpp"
#include "math.hpp"

class Player: public Entity
{
private:
    //water amount
    float max_water;
    float cur_water;
    //heatlh
    float max_hp;
    float cur_hp;

    Vector2f velocity;
    int speed;
    
public:
    Player(Vector2f p_pos, SDL_Texture* p_tex);
    void setVelocityX(int p_vel);
    void setVelocityY(int p_vel);
    Vector2f getVelocity();
    void update();
    void updateFrame();
    void updatePos();
    };

