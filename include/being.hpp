#pragma once
#include <iostream>
#include <string>


#include "entity.hpp"
#include "timer.hpp"


class Being : public Entity
{
protected:
    Timer timer;
    Vector2f velocity;
    int speed;
    string direction;
    string prevDirection;

    float maxHp;
    float curHp;

    int tileSize = 16;

    

public:
    Being(Vector2f p_pos, SDL_Texture* p_tex, float p_maxHp);

    void setVelocityX(int p_vel);
    void setVelocityY(int p_vel);
    
    Vector2f getVelocity();
    void update();
    void updateFrame();
    void updatePos();
    void setDirection();

};

