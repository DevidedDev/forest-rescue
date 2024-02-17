#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.hpp"
namespace utils
{
    

    inline void writeCamPos(){
    std::cout << "PLAYER" << std::endl;
    std::cout << "GRID POS: " <<"X: " << game::player.getPos().x/16 << "Y:" << game::player.getPos().y/16 << std::endl;

    std::cout << "X: " << game::player.getPos().x << "Y:" << game::player.getPos().y << std::endl;

    std::cout <<"DEST POS: "<<"X: " << game::player.getDestPos().x << "Y:" << game::player.getDestPos().y << std::endl;
    }

};


