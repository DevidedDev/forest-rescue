#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/input.hpp"
#include "../include/game.hpp"
#include "../include/files.hpp"


Keyboard::Keyboard(){
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }
    
}

void Keyboard:: getKey(SDL_Event& event,  bool key_down){
    //SDL_Keysym sym = event.key.keysym.sym;
    if(!strcmp(game::mode, "GAME")){

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

            case SDLK_ESCAPE:
                //change game mode to menu

                fileSys::saveLevel();
                //strcpy(game::mode, "MENU");
                game::finishGame();
                delete game::level;
                game::level = nullptr;
                break;

            default:
                //std::cout << "Key pressed: " <<  SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                break;
        };
    //DETECT BUTTON PRESSES
    }else if(!strcmp(game::mode, "MENU")){
        const char *key = SDL_GetKeyName(event.key.keysym.sym);
        std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        if(!strcmp(key,   "Backspace")){
            game::menu.getNameField().removeChar();
        }else if(!strcmp(key,   "Return")){
            game::menu.getNameField().changeState(0);
        }else if(strlen(key) == 1){
            char input_c = key[0];
            if((input_c >= 'A' && input_c <= 'Z')
                ||
                (input_c >= '0' && input_c <= '9')
            ){
                game::menu.getNameField().addChar(input_c+32);
            }
        }

    }else if(!strcmp(game::mode, "PAUSE")){

    }else{
        std::cout << "MODE ERROR: Nonexistent game mode for input sector" << std::endl;
    }
}

void Mouse::getBtn(SDL_Event& event){
    switch(event.button.button){
        case SDL_BUTTON_LEFT:
            if(!strcmp(game::mode, "MENU")){
                int m_x;
                int m_y;
                SDL_GetMouseState(&m_x,  &m_y);
                if(math::isInBounds(game::menu.getNameField().getRect(), Vector2f(m_x, m_y))){
                    std::cout << "Pressed on name field" << std::endl;
                    game::menu.getNameField().changeState();
                }
                else if(math::isInBounds(game::menu.getRandomNameBtn().getRect(), Vector2f(m_x, m_y))){
                    std::cout << "Pressed on random name btn" << std::endl;
                    game::menu.getNameField().setRandomName();

                }else if(math::isInBounds(game::menu.getStartBtn().getRect(), Vector2f(m_x, m_y))){
                    std::cout << "Pressed on start btn" << std::endl;
                    game::resetLevel();
                    strcpy(game::mode, "GAME");
                }else if(math::isInBounds(game::menu.getContinueBtn().getRect(), Vector2f(m_x, m_y))){
                    std::cout << "Pressed on continue btn" << std::endl;
                    strcpy(game::mode, "GAME");
                    fileSys::openLevel();
                    std::cout << "Level opened well" <<std::endl,
                    std::cout <<"changed game mode" << std::endl;
                }
                
                if(!math::isInBounds(game::menu.getNameField().getRect(), Vector2f(m_x, m_y))){
                   game::menu.getNameField().changeState(0);
                }
            }
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
            if(!strcmp(game::mode, "GAME"))
                keyboard.getKey(event,  0);
            break;
        default:
            break;
        }
    }
}