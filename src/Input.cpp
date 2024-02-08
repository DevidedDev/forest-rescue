#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/input.hpp"
#include "../include/player.hpp"


using namespace std;





Keyboard::Keyboard(){
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }
    
}

void Keyboard:: getKey(SDL_Event& event, Player& p_player){
    //SDL_Keysym sym = event.key.keysym.sym;
    
    
        switch(event.key.keysym.sym){


            case SDLK_w: //up
                p_player.getPos().y.operator--();
                break;
                
            case SDLK_s: // down
                p_player.getPos().y.operator++();
                break;

            case SDLK_a:
                p_player.getPos().x.operator--();
                break;

            case SDLK_d:
                p_player.getPos().x.operator++();
                break;

            default:
                cout << "Key pressed: " <<  SDL_GetKeyName(event.key.keysym.sym) << endl;
                break;
        };
        

}

void Mouse::getBtn(SDL_Event& event, Player& p_player){
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

void Input::getInput(bool& p_gameRunning, Player& p_player){
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            p_gameRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouse.getBtn(event, p_player);
            break;
        
        case SDL_KEYDOWN:
            keyboard.getKey(event, p_player);
            break;
        
        

        default:
            break;
        

        }
        
    }
}