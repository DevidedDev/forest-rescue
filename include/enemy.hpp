#pragma once

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "being.hpp"


class Enemy: public Being
{
private:
public:
    Enemy();
    Enemy(const Enemy& p_enym);
    Enemy(Vector2f p_pos);
    void followPlayer();
    void cutTree();
    void move();
    void update();
    bool isIdle();
    Vector2f getTilePos();


};

#endif //ENEMY_HPP