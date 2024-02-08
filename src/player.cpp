#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/player.hpp"
#include "../include/math.hpp"




Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
    :Entity(p_pos, p_tex, 0)
    {
        speed = 2;
        velocity.x = 0;
        velocity.y = 0;
        max_water = 100.0f;
        cur_water = 100.0f;
        
        max_hp = 100.0f;
        cur_hp = 100.0f;
    }
