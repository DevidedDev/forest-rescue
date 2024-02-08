#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/entity.hpp"
#include "../include/math.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_frame)
:pos(p_pos), dest_pos(pos), tex(p_tex)
//starting position = actual position
{   
    int tile_size = 16;
    currentFrame.x = p_frame * 16;
    currentFrame.y = 0;
    currentFrame.w = tile_size;
    currentFrame.h = tile_size;
}



SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}

SDL_Texture* Entity::getTex(){
    return tex;
}


void Entity::changeFrame(int p_frame){
    currentFrame.x = p_frame * tile_size;

}
