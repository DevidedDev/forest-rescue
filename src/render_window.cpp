#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "../include/render_window.hpp"
#include "../include/entity.hpp"
#include "../include/game.hpp"





RenderWindow::RenderWindow(const char* p_title, int p_width, int p_heigth)
    :window(NULL), renderer(NULL)
{

    window = SDL_CreateWindow(
        p_title, 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        p_width, 
        p_heigth,
        SDL_WINDOW_SHOWN
);

    if(window == NULL){
        std::cout << "Window failed to init. ERROR:" << SDL_GetError() << std::endl;
    }
    //creates renderer (window_to_render, use first ok graphics driver, use gpu if possible)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); 

    black.r= 255;
    black.g = 255;
    black.b = 255;
    black.a = 255;
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL){
        std::cout << "Failed to load texture. error:" << SDL_GetError() << std::endl;
    }
    return texture;
}


int RenderWindow::getRefreshRate(){
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

void RenderWindow::cleanUp(){
    SDL_DestroyWindow(window);
}

void RenderWindow::clear(){ //počisti renderer
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Player& p_ent){ //
    // NULL src  & texture fills whole screen

    // KATERA SLIKO ANIMACIJE HOČEM? (pogleda koordinate in velikosti znotraj png-ev)
    SDL_Rect src = p_ent.getCurrentFrame();  
    src.x = p_ent.getCurrentFrame().x*game::TILE_SIZE;
    src.y = p_ent.getCurrentFrame().y*game::TILE_SIZE;
    
    //to kar se dejansko nariše
    SDL_Rect dest;
    dest.x = p_ent.getDestPos().x * game::SCALER;
    dest.y = p_ent.getDestPos().y * game::SCALER;
    dest.w = src.w * game::SCALER;
    dest.h = src.h * game::SCALER;
    
    SDL_RenderCopy(renderer, p_ent.getTex(), &src, &dest);
}

void RenderWindow::render(Entity& p_ent){ //
    // NULL src  & texture fills whole screen

    // KATERA SLIKO ANIMACIJE HOČEM? (pogleda koordinate in velikosti znotraj png-ev)
    SDL_Rect src = p_ent.getCurrentFrame();  
    src.x = p_ent.getCurrentFrame().x*game::TILE_SIZE;
    src.y = p_ent.getCurrentFrame().y*game::TILE_SIZE;
    
    //to kar se dejansko nariše
    SDL_Rect dest;
    dest.x = p_ent.getDestPos().x * game::SCALER;
    dest.y = p_ent.getDestPos().y * game::SCALER;
    dest.w = src.w * game::SCALER ;
    dest.h = src.h * game::SCALER;

    SDL_RenderCopy(renderer, p_ent.getTex(), &src, &dest);
}


void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}

//TEST STUFF


void RenderWindow::renderText(const char* p_text_val, SDL_Color p_color, Vector2f p_pos){

    TTF_Font *font = TTF_OpenFont("../res/dev/munro.ttf", 40);

    SDL_Surface* textSurface  = TTF_RenderText_Solid(font, p_text_val, p_color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;

    textRect.x = p_pos.x;
    textRect.y = p_pos.y;
    SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);


    SDL_RenderCopy(renderer, text , NULL, &textRect);

    SDL_FreeSurface(textSurface);

    delete font;
    font = nullptr;
    textSurface = nullptr;
}



