#include <string>
#include "../include/being.hpp"
#include "../include/game.hpp"

Being::Being(Vector2f p_pos, SDL_Texture* p_tex, float p_maxHp)
:Entity(p_pos, p_tex, 0)
{
    direction = "IDLE";

    maxHp = 100.0f;
    curHp = maxHp;

    tileSize = 16;
    speed = 50;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
}

void Being::setVelocityX(int p_vel)
{
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
{
    //pitagorov izrek za diagonalno premikanje
    //float length = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    //"normaliziraj", če se premikaš diagonalno
    /*
    if (length != 0.0f) {
        velocity.x /= length;
        velocity.y /= length;
    }
    */
    
    //change position
    pos.x += velocity.x * speed * game::timer.getDT();
    pos.y += velocity.y * speed * game::timer.getDT();
    
}

void Being::updateFrame()
{
    timer.setCurent(game::timer);
    timer.setDT();
    int framesToUpdate = floor(timer.getDT() / (1.0f / game::animatedFPS));
    if (framesToUpdate > 0) {
        currentFrame.x += framesToUpdate;
        
        timer.setLastUpdate();
        if(direction=="IDLE"){
            currentFrame.y = 0;
            currentFrame.x %= 3;
        }else if(direction=="UP"){
            currentFrame.x %= 2;
            currentFrame.y = 2;
        }else if(direction=="DOWN"){
            currentFrame.x %= 2;
            currentFrame.y = 1;
            cout << currentFrame.x << endl;
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