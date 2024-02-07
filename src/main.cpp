#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/render_window.hpp" // hpp files just copy pastes files data, where the include tag is
#include "../include/entity.hpp"
#include "../include/utils.hpp"
#include "../include/input.hpp"

using namespace std;

int main(int argc, char *args[]){
    if(SDL_Init(SDL_INIT_VIDEO)> 0)
    {
        cout << "SDL_Init Failed. SDL_ERROR" << SDL_GetError() << endl;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG_Init Failed. Error:" << SDL_GetError() << endl;
    }

    RenderWindow window("Game", 1200, 700);

    //Writes out refresh rate
    //cout << window.getRefreshRate() << endl;

    SDL_Texture* grassTexture = window.loadTexture("../res/gfx/grass_texture.jpg");
    
    vector<Entity> entities;
   
    for(int i = 0; i < 12; i++){
        entities.push_back(Entity(Vector2f(i*30,150),grassTexture));
    }


    bool gameRunning = true;

    
    Input input;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSecods();


    while(gameRunning){
        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeInSecods();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while(accumulator >= timeStep){
            //Get controls and events
            input.getInput(gameRunning);
            
            accumulator -= timeStep;

        }
        //time left in accumulator in %
        const float alpha = accumulator / timeStep; 
        
        window.clear();
        //če ne dodaš "&" bo  ustvaril kopijo, maesto uporabljal original
        for(Entity& ent : entities){
            window.render(ent);
        }
          
        
        window.display();

        int frameTicks = SDL_GetTicks() - startTicks;

        if( frameTicks < 1000 / window.getRefreshRate()){
            SDL_Delay(1000 / window.getRefreshRate()- frameTicks);
        }
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}