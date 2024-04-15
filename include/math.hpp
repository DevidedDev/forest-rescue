#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>






struct Vector2f
{
    
    float x,y;
    Vector2f();
    Vector2f(float p_x, float p_y);
    Vector2f operator*(float p_n);
    Vector2f operator/(float p_n);
};

struct Dimension{
    int w,h;
    Dimension();
    Dimension(int p_w, int p_h);
};




