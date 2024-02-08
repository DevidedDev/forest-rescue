#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/entity.hpp"
#include "../include/math.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_frame)
:pos(p_pos), tex(p_tex)
{   
    int scaler = 16;
    currentFrame.x = p_frame * scaler;
    currentFrame.y = 0;
    currentFrame.w = 16;
    currentFrame.h = 16;
}



SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}

SDL_Texture* Entity::getTex(){
    return tex;
}


void Entity::changeFrame(int p_frame){
    currentFrame.x = p_frame*scaler;

}
