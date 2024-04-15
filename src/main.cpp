#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <list>
#include <time.h>

#include "../include/includes.hpp"


int main(int argc, char *args[]){
    srand(time(0));

    delete game::level;
    game::difficulty = 0;
    game::level = new Level();
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

    //TEST
    // TTF_Font *font = TTF_OpenFont("../res/dev/munro.ttf", 20);
    // SDL_Color color = {144, 77, 255, 255};
    // SDL_Surface *textSurface = TTF_RenderText_Solid (font, "COOL GAME MAN!", color);
    // SDL_Texture *text = SDL_CreateTextureFromSurface(game::window.getRenderer(), textSurface);
    // SDL_Rect textRect;
    // textRect.x = textRect.y = 0;
    // SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);

    // SDL_FreeSurface(textSurface);

    // textSurface = nullptr;

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
    //test
        // testEnemy.update();
        // game::window.render(testEnemy);
        // testEnemy.detectCollision(game::player);
        // testTribesman.update();
        // game::window.render(testTribesman);
        // testFire.update();
        // if(testFire.putOut()){
        //     std::cout << "Tile put out";
        // }
        // if(testFire.destroyTile()){
        //     std::cout << "Tile destroyed";
        // }
        // game::window.render(testFire);

        //game::window.drawNormalText();
        //SDL_RenderCopy(game::window.getRenderer(), text, NULL, &textRect);
        
        game::window.display();

        //delay
        game::timer.capFrames();

        
        if(game::level->checkLevelFinished()){
            delete game::level;
            game::level = new Level();
        }

        if(game::level->checkGameEnd()){
            game::gameRunning= false;
        }
    }

 
    game::window.cleanUp();

    delete game::level;
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