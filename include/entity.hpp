#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "math.hpp"

class Entity{
protected:
    int tile_size;
    Vector2f pos; //ACTUAL POSITION
    Vector2f dest_pos; //DISPLAYED POSITION
    Dimension dimension; //width & height

    SDL_Rect currentFrame; //x, y, h & w of current frame. 
    SDL_Texture* tex; // texture

public:

    Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_frame);
    Entity();
    Entity(const Entity& e);
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTex();
    Vector2f& getPos();
    Vector2f& getTilePos();
    Vector2f& getDestPos();
    Dimension& getDimension();
    
    void updateFrame(int p_frame); //only for x axis
    void update();
    void updateFramePos(Vector2f p_vec);
};