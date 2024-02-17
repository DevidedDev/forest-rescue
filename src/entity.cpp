#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/entity.hpp"
#include "../include/math.hpp"
#include "../include/game.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_frame)
:pos(p_pos), dest_pos(pos), tex(p_tex)
//starting position = actual position
{   
    int tile_size = 16;
    currentFrame.x = p_frame;
    currentFrame.y = 0;
    currentFrame.w = tile_size;
    currentFrame.h = tile_size;
}



Entity::Entity(const Entity& e){
    pos = e.pos;
    dest_pos = pos;
    tex = e.tex;
    tile_size = e.tile_size;
    currentFrame.x = e.currentFrame.x;
    currentFrame.y = e.currentFrame.y;
    currentFrame.w = e.tile_size;
    currentFrame.h = e.tile_size;
    //std:: cout << "Entity" << std::endl;
}

Entity::Entity(){
    tex = nullptr;
};




SDL_Rect Entity::getCurrentFrame(){
    return currentFrame;
}

SDL_Texture* Entity::getTex(){
    return tex;
}


void Entity::updateFrame(int p_frame){
    currentFrame.x = p_frame * game::TILE_SIZE;
}

void Entity::update(){
    dest_pos.x = pos.x - game::camera.x;
    dest_pos.y = pos.y - game::camera.y;
}