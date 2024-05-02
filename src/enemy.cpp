#include "../include/enemy.hpp"
#include "../include/game.hpp"

Enemy::Enemy(Vector2f p_pos)
:Being
    (
        p_pos,
        game::textures.enemy, 
        100.0f
    )
{
    vision = 3*16;
    tileSize = game::TILE_SIZE;
    speed = 40;
}

Enemy::Enemy(){}

Enemy::Enemy(const Enemy& p_enym)
:Being
    (
        Vector2f(
            p_enym.pos.x/16,
            p_enym.pos.y/16
            ),
        game::textures.enemy, 
        100.0f
    )
{   
    vision = 3*16;
    tileSize = game::TILE_SIZE;
    speed = 40;

}

void Enemy::followPlayer(){
    
    if(game::player.getPos().x > pos.x+dimension.w){
        setVelocityX(1);
    }else if(game::player.getPos().x+dimension.w < pos.x){
        setVelocityX(-1);
    }else{
        setVelocityX(0);
    }
    if(game::player.getPos().y > pos.y+dimension.h){
        setVelocityY(1);
    }else if(game::player.getPos().y +dimension.h< pos.y){
        setVelocityY(-1);
    }else{
        setVelocityY(0);
    }
};

void Enemy::cutTree(){

};




void Enemy::move(){
    if( isInVisibleRange(game::player) ){
        followPlayer();
        //std::cout << "I see player" << std::endl;
    }else{
        wander();
       // std::cout << "NO see" << std::endl;
    }
}


void Enemy::update()
{
    dest_pos.y = pos.y - game::camera.y;
    dest_pos.x = pos.x - game::camera.x;
    // animation
    move();
    updatePos();
    setDirection();
    updateFrame();
}
bool Enemy::isIdle(){
    return (getVelocity().x == 0 && getVelocity().y == 0);
}


Vector2f Enemy::getTilePos(){
    return getPos()/16;
}

