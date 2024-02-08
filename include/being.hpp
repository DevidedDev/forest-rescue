#pragma once
#include "includes.hpp"

class Being:public Entity
{
    
    private:
        short speed;
        Vector2f velocity;
    public:
        Being(Vector2f p_pos, SDL_Texture* p_tex, int p_frame, int p_speed);
        Vector2f getVelocity();
};

