#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/math.hpp"

#include <iostream>




Vector2f::Vector2f(float p_x, float p_y){
    x = p_x;
    y = p_y;
}

Vector2f::Vector2f(){
    x = 0.0f;
    y = 0.0f;
}

Vector2f Vector2f::operator*(float p_n){
    return Vector2f(
        this-> x * p_n,
        this-> y * p_n
    );

}

Vector2f Vector2f::operator/(float p_n){
    return Vector2f(
        this-> x / p_n,
        this-> y / p_n
    );

}


Dimension::Dimension()
:w(0), h(0)
{}

Dimension::Dimension(int p_w, int p_h)
:w(p_w), h(p_h)
{}


bool math::isInBounds(SDL_Rect p_rect, Vector2f p_pos2){
    if(
        (
            p_rect.x <= p_pos2.x
            &&
            p_rect.x + p_rect.w >= p_pos2.x
        )
        &&
        (
            p_rect.y <= p_pos2.y
            &&
            p_rect.y + p_rect.h >= p_pos2.y
        )
    )
    return 1;

    
    return 0;
}