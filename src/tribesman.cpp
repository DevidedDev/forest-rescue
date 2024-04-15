#include "../include/tribesman.hpp"
#include "../include/game.hpp"

Tribesman::Tribesman(Vector2f p_pos, Dimension p_dim)
:Being(
    Vector2f
    (
    p_pos.x+rand()%3,
    p_pos.y+rand()%3
    ),
    game::textures.tribesmen, 
    100.0f
    ),
vilagePos(p_pos),
vilageSize(p_dim)
{
    vision = 3*16;
    tileSize = game::TILE_SIZE;
    speed = 42;
}



void Tribesman::move(){
    if(returnHome()){
        
    }else{
        wander();
    }
}



void Tribesman::update()
{
    dest_pos.y = pos.y - game::camera.y;
    dest_pos.x = pos.x - game::camera.x;
    // animation
    move();
    updatePos();
    setDirection();
    updateFrame();
}

bool Tribesman::returnHome(){
    bool isTrue = false;
    
    if(pos.x/16 < vilagePos.x - 3 ){
        velocity.x = 1;
        isTrue = true;
        
    }else if(pos.x/16 > vilagePos.x + vilageSize.w + 3 ){
        velocity.x = -1;
        isTrue = true;
    }
    

    if(pos.y/16 < vilagePos.y - 3){
        velocity.y = 1;
        isTrue = true;
        
    }else if(pos.y/16 > vilagePos.y  + vilageSize.h + 3){
        velocity.y = -1;
        isTrue = true;
    }

    return isTrue;

}
