#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/input.hpp"


using namespace std;





Keyboard::Keyboard(){
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }
    
}

void Keyboard:: getKey(SDL_Event& event){
        switch(event.key.keysym.sym){
            case SDLK_w: //up
                
                break;
            case SDLK_s: // down
                break;

            default:
                cout << "Key pressed: " <<  SDL_GetKeyName(event.key.keysym.sym) << endl;
                break;
        };

}

void Mouse::getBtn(SDL_Event& event){


}

void Input::getInput(bool& p_gameRunning){
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            p_gameRunning = false;
            break;
        
        case SDL_KEYDOWN:
            keyboard.getKey(event);
        
        case SDL_MOUSEBUTTONDOWN:
            mouse.getBtn(event);
        default:
            break;
        

        }
        
    }
}