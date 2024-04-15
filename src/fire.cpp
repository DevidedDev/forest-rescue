#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/fire.hpp"
#include "../include/game.hpp"

Fire::Fire(Vector2f p_pos)
:Entity(p_pos, game::textures.fire, 0),
burnTime(20000),
isSpread(false)
{
};


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
    if(game::timer.getCurent() - burnStart >= burnTime){
        //std::cout << "Burning time" << timer.getCurent() - burnStart << std::endl;
        currentFrame.x = 0;
        return true;
    }
    return false;
}


int Fire::getBurnStart(){
    return burnStart;
}


int Fire::getLastSpread(){
    return lastSpread;

}

void Fire::setLastSpread(){
    lastSpread = game::timer.getCurent();
    isSpread = true;
}


