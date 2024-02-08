#include "../include/entity.hpp"
#include "../include/being.hpp"

Being::Being(Vector2f p_pos, SDL_Texture* p_tex, int p_frame, int p_speed)
:Entity(p_pos, p_tex, p_frame), speed(p_speed)
{
    velocity.x = 0;
    velocity.y = 0;
}

Vector2f Being::getVelocity(){
    return velocity;
};
    