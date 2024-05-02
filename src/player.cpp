#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/player.hpp"
#include "../include/game.hpp"

Player::Player( SDL_Texture* p_tex)
:Being(Vector2f(0,0), p_tex, 100.0f)
{   
    vision = 3 * game::TILE_SIZE;
    tileSize = game::TILE_SIZE;
    max_water = 100.0f;
    cur_water = 100.0f;
}