#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "../include/includes.hpp"

using namespace std;

int main(int argc, char *args[]){
    srand(time(0));

    if(SDL_Init(SDL_INIT_VIDEO)> 0)
    {
        cout << "SDL_Init Failed. SDL_ERROR" << SDL_GetError() << endl;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        cout << "IMG_Init Failed. Error:" << SDL_GetError() << endl;
    }


    //ENTITIES
    int n= game::lvlGrid.w;
    int m = game::lvlGrid.h; 
    vector <vector <Entity> > tiles;


     for(int i = 0; i < n; i++){
        vector<Entity> innerVec;
        for(int j = 0; j < m; j++){
            innerVec.push_back(Entity(Vector2f(i*16,j*16),game::textures.grass, rand()%5));
        }
        tiles.push_back(innerVec);
    }
    

    Input input;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::hireTimeInSecods();


    while(game::gameRunning){
        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeInSecods();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while(accumulator >= timeStep){
            //Get controls and events
            input.getInput();
            
            accumulator -= timeStep;

        }
        //time left in accumulator in %
        const float alpha = accumulator / timeStep; 
        
        game::window.clear();
        
        game::update();

        //CAMERA
        /*
        
        
        camera.x = game::player.getPos().x - (1280/2); //screen size
        camera.y = game::player.getPos().y - (720/2);
        if(camera.x < 0){
            camera.x = 0;
        }
        if(camera.y = 0){
            camera.y = 0;
        }
        if(camera.x > camera.w )
            camera.x = camera.w;
        if(camera.y > camera.h)
            camera.y = camera.h;
        */
        

        for(int i = 0;  i < n; i++){
            vector<Entity>* innerVec = &tiles.at(i);
            for(int j = 0; j < m; j++){
                (*(&(innerVec->at(j)))).update();
                game::window.render(*(&(innerVec->at(j))));
               
            }
        }
        
        game::window.render(game::player);
          
        
        game::window.display();

        int frameTicks = SDL_GetTicks() - startTicks;

        if( frameTicks < 1000 / game::window.getRefreshRate()){
            SDL_Delay(1000 / game::window.getRefreshRate()- frameTicks);
        }
    }

    game::window.cleanUp();
    SDL_Quit();

    return 0;
}