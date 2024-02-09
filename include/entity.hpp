#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "math.hpp"

class Entity{
protected:
    
    int tile_size;
    Vector2f pos; //ACTUAL POSITION
    Vector2f dest_pos; //DISPLAYED POSITION
    


    SDL_Rect currentFrame; //x, y, h & w of current frame. ( moje so vse na isti liniji, tako da moram samo x posodobit.)
    SDL_Texture* tex; // texture

public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_frame);
    
    SDL_Rect getCurrentFrame();
    SDL_Texture* getTex();
    Vector2f& getPos(){
        return pos;
    };
    Vector2f& getDestPos(){
        return dest_pos;
    };
    void updateFrame(int p_frame);
    void update();

};