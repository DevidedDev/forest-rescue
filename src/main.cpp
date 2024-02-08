#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/render_window.hpp" // hpp files just copy pastes files data, where the include tag is
#include "../include/entity.hpp"
#include "../include/utils.hpp"
#include "../include/input.hpp"
#include "../include/textures.hpp"
#include "../include/player.hpp"

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

    //cout << window.getRefreshRate() << endl;

    //TEXTURES
    Textures textures(window);

    //ENTITIES
    int n= 20;
    int m =20;
    vector <Entity> tiles;
    Player player(Vector2f(0, 0), textures.player);

    for(int i = 0; i < n; i++){
        tiles.push_back(Entity(Vector2f(i*16, 0), textures.grass));
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
            input.getInput(gameRunning, player);
            
            accumulator -= timeStep;

        }
        //time left in accumulator in %
        const float alpha = accumulator / timeStep; 
        
        window.clear();
        //če ne dodaš "&" bo  ustvaril kopijo, maesto uporabljal original
        // for(int i = 0; i < n; i++){
        // for (int j = m; j < m; j++){
        //     window.render(grassTiles[i][j]);
        // }
        //    }
        for(int i = 0; i < n; i++){
            window.render(tiles.at(i));
        }   
        
        window.render(player);
          
        
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