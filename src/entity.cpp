#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/entity.hpp"
#include "../include/math.hpp"
#include "../include/game.hpp"

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, int p_frame)
:pos(Vector2f(p_pos.x *game::TILE_SIZE, p_pos.y *game::TILE_SIZE)), dest_pos(pos), tex(p_tex)
//starting position = actual position
{   
    int tile_size = game::TILE_SIZE;
    currentFrame.x = p_frame;
    currentFrame.y = 0;
    currentFrame.w = tile_size;
    currentFrame.h = tile_size;
    dimension.w = tile_size;
    dimension.h = tile_size;
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
    dimension.w = tile_size;
    dimension.h = tile_size;
    //std:: cout << "Entity" << std::endl;
}

Entity::Entity(){
    tex = nullptr;
};

Vector2f& Entity::getPos(){
        return pos;
    };

Vector2f& Entity::getTilePos(){
    Vector2f tmp = getPos();
    tmp.x /= game::TILE_SIZE;
    tmp.y /= game::TILE_SIZE;
    return tmp;
}

Vector2f& Entity::getDestPos(){
    return dest_pos;
}

Dimension& Entity::getDimension(){
    return dimension;
}

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

void Entity::updateFramePos(Vector2f p_pos){
    currentFrame.x = p_pos.x;
    currentFrame.y = p_pos.y;

}
