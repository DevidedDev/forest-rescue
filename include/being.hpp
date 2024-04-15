#pragma once
#include <iostream>
#include <string>


#include "entity.hpp"
#include "timer.hpp"


class Being : public Entity
{
protected:
    int vision;
    Timer timer;
    int wanderInterval; //how long to do 1 move
    int lastUpdate; //for random movement
    Vector2f velocity;
    int speed;
    std::string direction;
    std::string prevDirection;

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

    bool detectCollision(Entity& p_entity);
    void takeDamage();
    void wander();
    bool isInVisibleRange(Entity& p_entity);

};

