#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>


using namespace std;


class Axes{
private:
    float value;
    
public:
    Axes();
    Axes(float p_val);
    
    float operator*(float p_multiplier);
    void operator++();
    void operator--();
    
};

struct Vector2f
{
    Axes x;
    Axes y;
    Vector2f();
    Vector2f(float p_x, float p_y);

};

