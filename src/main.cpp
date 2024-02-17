#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "../include/includes.hpp"


int main(int argc, char *args[]){
    delete game::level;
    game::level = new Level();
    srand(time(0));

    if(SDL_Init(SDL_INIT_VIDEO)> 0)
    {
        std::cout << "SDL_Init Failed. SDL_ERROR" << SDL_GetError() << std::endl;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG_Init Failed. Error:" << SDL_GetError() << std::endl;
    }

    //OTHER SETTUP
    Input input;

    while(game::gameRunning){
        game::timer.setStart();

        input.getInput();
    
        //time left in accumulator in %
        game::timer.setCurent();

        game::timer.setDT();
        //movement
        game::update();
        

        //End frame timing
        game::timer.setLastUpdate();
        game::timer.setEnd();
        
        // std::cout << "p-x: " << game::player.getPos().x/16;
        // std::cout << " p-y: " <<game::player.getPos().y/16<< std::endl;

        //RENDERING 
        game::window.clear();
        //game::level.render();
        
 
        game::level->render();
        game::window.render(game::player);
        game::window.display();

        //delay
        game::timer.capFrames();
        
    }

 
    game::window.cleanUp();

    delete game::level;
    game::level = nullptr;
    SDL_Quit();

    return 0;
}