#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/player.hpp"
#include "../include/game.hpp"




Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex, 0)
    {
        tile_size = 16;
        speed = 16;
        velocity.x = 0.0f;
        velocity.y = 0.0f;
        max_water = 100.0f;
        cur_water = 100.0f;
        
        max_hp = 100.0f;
        cur_hp = 100.0f;
    }

void Player::setVelocityX(int p_vel){
    velocity.x = p_vel;
}

void Player::setVelocityY(int p_vel){
    velocity.y = p_vel;
}

Vector2f Player::getVelocity(){
    return velocity;
}

void Player::update(){
    dest_pos.y = pos.y - game::camera.y;
    dest_pos.x = pos.x - game::camera.x;
    
    cout << "GRID POS: " <<"X: " << pos.x/16 << "Y:" << pos.y/16 << endl;

    cout << "X: " << pos.x << "Y:" << pos.y << endl;

    cout <<"DEST POS: "<<"X: " << dest_pos.x << "Y:" << dest_pos.y << endl;
    updatePos(); 
    updateFrame();
}

void Player::updatePos(){
    pos.x += velocity.x *speed;
    pos.y += velocity.y*speed;
    
}

void Player::updateFrame(){
    if(velocity.x == 0){
        Entity::updateFrame(0);
        
    }else if(velocity.x > 0){
        Entity::updateFrame(8);

    }else if(velocity.x < 0){
        Entity::updateFrame(10);
    }
    
    if(velocity.y > 0){
        Entity::updateFrame(3);
    }else if(velocity.y < 0){
        Entity::updateFrame(5);
    }
    
}