#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <cstring>

#include "../include/includes.hpp"


int main(int argc, char *args[]){
    srand(time(0));

    // delete game::level;
    // game::difficulty = 0;
    // game::level = new Level();
    // Enemy testEnemy;
    //Entity testEnt(Vector2f(1,1), game::textures.grass, 0);

    if(SDL_Init(SDL_INIT_VIDEO)> 0)
    {
        std::cout << "SDL_Init Failed. SDL_ERROR" << SDL_GetError() << std::endl;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG_Init Failed. Error:" << SDL_GetError() << std::endl;
    }

    if( TTF_Init() == -1 )
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error:"  << TTF_GetError() << std::endl;
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

        
        
        

        //End frame timing
        game::timer.setLastUpdate();
        game::timer.setEnd();   
        
        // std::cout << "p-x: " << game::player.getPos().x/16;
        // std::cout << " p-y: " <<game::player.getPos().y/16<< std::endl;

        //RENDERING 
        game::window.clear();
        //game::level.render();
        
        game::update();

        game::window.display();

        

        if(!strcmp(game::mode, "GAME")){
            if(game::level->checkLevelFinished()){
                game::addPlayerScore();
                game::difficulty++;
                delete game::level;
                game::level = new Level();
            }
            if(game::level->checkGameEnd()){
                //strcpy(game::mode, "MENU")";
                game::finishGame();
                
                std::cout << "END OF GAME!!!" << std::endl;
            }
            // if(game::gameRunning = false){
            //     fileSys::saveScore(Score(game::playerName, game::playerScore));
            //     strcpy(game::mode, "MENU");
            //     remove(fileSys::LVL_FILE_PATH);
            // }
        }
        
        
        //delay
        game::timer.capFrames();
        
   
        
        
        
        

        
    }

 
    game::window.cleanUp();
    if(game::level != nullptr){
        delete game::level;
    }
    game::level = nullptr;
    //delete vil;
    //vil = nullptr;
    //TEST
   // SDL_DestroyTexture(text);
    //text = nullptr;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

