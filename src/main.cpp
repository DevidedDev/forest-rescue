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



    while(game::gameRunning){
        game::timer.setStart();



        
        input.getInput();
            
            

    
        //time left in accumulator in %
        
        game::window.clear();
        
        game::update();


        for(int i = 0;  i < n; i++){
            vector<Entity>* innerVec = &tiles.at(i);
            for(int j = 0; j < m; j++){
                (*(&(innerVec->at(j)))).update();
                game::window.render(*(&(innerVec->at(j))));
               
            }
        }
        
        game::window.render(game::player);
          
        
        game::window.display();

        game::timer.setEnd();
        game::timer.update();
        game::timer.capFrames();


        
    }

    game::window.cleanUp();
    SDL_Quit();

    return 0;
}