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
    switch(event.button.button){
        case SDL_BUTTON_LEFT:
            cout << "L-mouse-btn pressed"<< endl;
            break;
        case SDL_BUTTON_RIGHT:
            cout << "R-mouse-btn pressed" << endl;
            break;
        default:
            break;
    } 

}

void Input::getInput(bool& p_gameRunning){
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            p_gameRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouse.getBtn(event);
            break;
        
        case SDL_KEYDOWN:
            keyboard.getKey(event);
            break;
        
        

        default:
            break;
        

        }
        
    }
}