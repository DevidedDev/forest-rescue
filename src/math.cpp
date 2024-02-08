#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/math.hpp"

#include <iostream>

Axes::Axes(){
    value = (0.0f);
};

Axes::Axes(float p_val)
    :value(p_val)
    {};


void Axes::operator++(){
    value++;
};

void Axes::operator--(){
    value--;
};

float Axes::operator*(float p_multiplier){
    return value*p_multiplier;

}




Vector2f::Vector2f(float p_x, float p_y){
    x = Axes(p_x);
    y = Axes(p_y);
}



