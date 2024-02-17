#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/input.hpp"
#include "../include/game.hpp"







Keyboard::Keyboard(){
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }
    
}

void Keyboard:: getKey(SDL_Event& event,  bool key_down){
    //SDL_Keysym sym = event.key.keysym.sym;
    
    
        switch(event.key.keysym.sym){


            case SDLK_w: //up
            
                game::player.setVelocityY(- key_down);
                break;
                
            case SDLK_s: // down
                game::player.setVelocityY(key_down);
                break;

            case SDLK_a:
                game::player.setVelocityX(- key_down);
                break;

            case SDLK_d:
                game::player.setVelocityX(key_down);
                break;

            default:
                //std::cout << "Key pressed: " <<  SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                break;
        };
        

}

void Mouse::getBtn(SDL_Event& event){
    switch(event.button.button){
        case SDL_BUTTON_LEFT:
            //std::cout << "L-mouse-btn pressed"<< std::endl;
            break;
        case SDL_BUTTON_RIGHT:
            //std::cout << "R-mouse-btn pressed" << std::endl;
            break;
        default:
            break;
    } 

}

void Input::getInput(){
    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            game::gameRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouse.getBtn(event);
            break;
        
        case SDL_KEYDOWN:
            keyboard.getKey(event,  1);
            break;

        case SDL_KEYUP:
            keyboard.getKey(event,  0);
            break;

        default:
            break;
        }
    }
}