#pragma once

#include "being.hpp"

class Tribesman: public Being
{
private:
    int vision;
    Vector2f vilagePos;
    Dimension vilageSize;
public:

    Tribesman(Vector2f p_pos, Dimension p_dim);
    void followPlayer();
    void move();
    void update();
    bool returnHome();

    //bool isInPlayerRange();
};