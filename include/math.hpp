#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include<iostream>


using namespace std;




struct Vector2f
{
    
    float x,y;
    Vector2f();
    Vector2f(float p_x, float p_y);
    
};

struct Dimension{
    int w,h;
    Dimension();
    Dimension(int p_w, int p_h);
};


