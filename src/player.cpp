#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/player.hpp"
#include "../include/game.hpp"




Player::Player(Vector2f p_pos, SDL_Texture* p_tex)
    :Being(p_pos, p_tex, 100.0f)
    {
        tileSize = 16;
        max_water = 100.0f;
        cur_water = 100.0f;
        
        
    }



