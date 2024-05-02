#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/fire.hpp"
#include "../include/game.hpp"

Fire::Fire(Vector2f p_pos)
:Entity(p_pos, game::textures.fire, 0)
{
    burnStart  = 0;
    lastSpread = 13;
};

Fire::Fire(const Fire& p_fire)
:Entity(Vector2f(
    p_fire.pos.x/16,
    p_fire.pos.y/16)
    
    , game::textures.fire, p_fire.currentFrame.x),
timer(p_fire.timer)
{   
    lastSpread = p_fire.lastSpread;
    burnStart = timer.getStart() +(p_fire.burnStart -  timer.getStart());
};

Fire::Fire(){};

void Fire::updateFrame(){
    timer.setCurent(game::timer);
    timer.setDT();
    int framesToUpdate = floor(timer.getDT() / (1.0f / game::animatedFPS));
    if (framesToUpdate > 0) {
        
        timer.setLastUpdate();
        if(currentFrame.x <= 1){
            currentFrame.x ++;
        }else{
            currentFrame.x = currentFrame.x % 3;
            currentFrame.x += 2;
        }
        

    }


}

void Fire::update(){
    if(currentFrame.x == 0){
        burnStart = game::timer.getCurent();
        lastSpread = game::timer.getCurent();
        
    }
    
    Entity::update();
    updateFrame();
    //if
    
}

bool Fire::putOut(){
    if( game::player.detectCollision(*this) ){
        currentFrame.x = 0;
        return true;
    }
    return false;
}


bool Fire::destroyTile(){
    if(game::timer.getCurent() - burnStart >= game::burnTime){
        //std::cout << "Burning time" << timer.getCurent() - burnStart << std::endl;
        currentFrame.x = 0;
        return true;
    }
    return false;
}

void Fire::setBurnStart(){
    burnStart = game::timer.getCurent();
}

int Fire::getBurnStart(){
    return burnStart;
}


int Fire::getLastSpread(){
    return lastSpread;

}

void Fire::setLastSpread(){
    lastSpread = game::timer.getCurent();
}


