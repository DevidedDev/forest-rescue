#include <string>
#include "../include/being.hpp"
#include "../include/game.hpp"

Being::Being(Vector2f p_pos, SDL_Texture* p_tex, float p_maxHp)
:Entity(p_pos, p_tex, 0),
wanderInterval(0),
direction("IDLE")
{
    lastUpdate =timer.getCurent();

    maxHp = p_maxHp;
    curHp = maxHp;

    tileSize = 16;
    speed = 50;
    velocity.x = 0.0f;
    velocity.y = 0.0f;

}

Being::Being(){
    
}

void Being::setVelocityX(int p_vel)
{
    // if(pos.x <= 0 && p_vel < 0){
    //     velocity.x = -(p_vel);
    // }else
        velocity.x = p_vel;
    
    
    
}

void Being::setVelocityY(int p_vel)
{
    velocity.y = p_vel;
}

Vector2f Being::getVelocity()
{
    return velocity;
}

void Being::update()
{
    dest_pos.y = pos.y - game::camera.y;
    dest_pos.x = pos.x - game::camera.x;
    // animation
    updatePos();
    setDirection();
    updateFrame();
}

void Being::updatePos()
{   //CHECK IF PLAYER INSIDE OF MAP
    if((!(pos.x <= 0  && velocity.x < 0))
        &&
        (!(pos.x+dimension.w >= game::lvlDimension.w && velocity.x > 0))
    ) pos.x += velocity.x * speed * timer.getDT();
   if((!(pos.y <= 0  && velocity.y < 0))
        &&
        (!(pos.y+dimension.h >= game::lvlDimension.h && velocity.y > 0))
    ) pos.y += velocity.y * speed * timer.getDT();
}

void Being::updateFrame()
{
    timer.setCurent(game::timer);
    timer.setDT();
    int framesToUpdate = floor(timer.getDT() / (1.0f / game::animatedFPS)); //NEEDS FIXING
    if (framesToUpdate > 0) {
        currentFrame.x += framesToUpdate;
        
        timer.setLastUpdate(); //!NEEDS FIXING
        if(direction=="IDLE"){
            currentFrame.y = 0;
            currentFrame.x %= 3;
        }else if(direction=="UP"){
            currentFrame.x %= 2;
            currentFrame.y = 2;
        }else if(direction=="DOWN"){
            currentFrame.x %= 2;
            currentFrame.y = 1;
            //cout << currentFrame.x << sendl;
        }else if(direction=="LEFT"){
            currentFrame.x %= 2;
            currentFrame.y = 4;
        }else if(direction=="RIGHT"){
            currentFrame.x %= 2;
            currentFrame.y = 3;
        }
    }
    
    
    


}

void Being::setDirection()
{
    if (velocity.x == 0 && velocity.y == 0)
    {
        direction = "IDLE";
        return;
    }

    if (velocity.x > 0)
    {
        direction = "RIGHT";
        return;
    }
    else if (velocity.x < 0)
    {
        direction = "LEFT";
        return;
    }

    if (velocity.y > 0)
    {
        direction = "DOWN";
    }       
    else if (velocity.y < 0)
    {
        direction = "UP";
    }
};

bool Being::detectCollision(Entity& p_entity){
    if(
        //BOTTOM RIGHT CORNER COLLISSION
        (
        pos.x <= p_entity.getPos().x+p_entity.getDimension().w
        &&
        pos.x + dimension.w >= p_entity.getPos().x+p_entity.getDimension().w
        ||
        pos.x + dimension.w >= p_entity.getPos().x
        &&
        pos.x <= p_entity.getPos().x
        )
        &&
        (
        pos.y <= p_entity.getPos().y+p_entity.getDimension().h
        &&
        pos.y+ dimension.h >= p_entity.getPos().y+p_entity.getDimension().h
        ||
        pos.y + dimension.h >= p_entity.getPos().y
        &&
        pos.y <= p_entity.getPos().y
        )

        // &&
        // pos.y <= p_entity.getPos().y+p_entity.getDimension().h
        // &&
        // pos.y >= p_entity.getPos().y+p_entity.getDimension().h
    )
    return true;
    
    
}

void Being::takeDamage(){
}


void Being::wander(){
    if( (timer.getCurent() - lastUpdate )> wanderInterval)

    {
        //IDLE
        if(getVelocity().x == 0 && getVelocity().y == 0 ){
            do{
                setVelocityX(rand()%3-1);
                setVelocityY(rand()%3-1);
            }while(getVelocity().x == 0 && getVelocity().y == 0 );
            
        }
        //S
        else{
            setVelocityX(0);
            setVelocityY(0);
        }
        lastUpdate = timer.getCurent();
        wanderInterval = rand()%1500+1000;
    }
    
}

bool Being::isInVisibleRange(Entity& p_entity){
if(
    //BOTTOM RIGHT CORNER COLLISSION
    (
    pos.x - vision <= p_entity.getPos().x+p_entity.getDimension().w 
    &&
    pos.x+ dimension.w + vision >= p_entity.getPos().x+p_entity.getDimension().w 
    ||
    pos.x + dimension.w + vision >= p_entity.getPos().x
    &&
    pos.x - vision <= p_entity.getPos().x 
    )
    &&
    (
    pos.y  - vision <= p_entity.getPos().y+p_entity.getDimension().h 
    &&
    pos.y + dimension.h  + vision>= p_entity.getPos().y+p_entity.getDimension().h 
    ||
    pos.y + dimension.h  + vision >= p_entity.getPos().y 
    &&
    pos.y - vision<= p_entity.getPos().y 
    )

    )
    return true;
}

void Being::setPos(Vector2f p_pos){
    pos = p_pos;
    
}
