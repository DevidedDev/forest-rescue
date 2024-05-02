#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

#include "../include/render_window.hpp"
#include "../include/entity.hpp"
#include "../include/game.hpp"
#include "../include/files.hpp"





RenderWindow::RenderWindow(const char* p_title, int p_width, int p_heigth)
    :window(NULL), renderer(NULL)
{

    if( TTF_Init() == -1 )
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error:"  << TTF_GetError() << std::endl;
    }

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


void RenderWindow::renderText(const char* p_text_val, SDL_Color p_color, Vector2f p_pos, int fontSize){

    TTF_Font *font = TTF_OpenFont("../res/dev/munro.ttf", fontSize);

    SDL_Surface* textSurface  = TTF_RenderText_Solid(font, p_text_val, p_color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect textRect;

    textRect.x = p_pos.x;
    textRect.y = p_pos.y;
    SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);


    SDL_RenderCopy(renderer, text , NULL, &textRect);

    SDL_DestroyTexture(text);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    //delete font;
    font = nullptr;
    textSurface = nullptr;
}

// void RenderWindow::renderButton(){
//     renderText(const char* p_text_val, SDL_Color p_color, Vector2f p_pos, int fontSize);
    
// }

void RenderWindow::renderButton(Button p_btn){
    SDL_Rect rect;
    rect.w = p_btn.getDim().w;
    rect.h = p_btn.getDim().h;
    rect.x = p_btn.getPos().x;
    rect.y = p_btn.getPos().y;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    //SDL_RenderPresent(renderer);
    renderText(p_btn.getTxt(), p_btn.getClr(), p_btn.getPos(), p_btn.getTxtSize());
}

void RenderWindow::renderMenu(){
    SDL_Rect src;  
    src.x = 0;
    src.y = 0;
    src.w = 1344;
    src.h = 768;

    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = src.w;
    dest.h = src.h;

    SDL_RenderCopy(renderer, game::textures.forest_bg, &src, &dest);

    renderText(
        "Player name:",
        Colors::white,
        Vector2f(
            game::WINDOW_WIDTH/2 + 250,
            game::WINDOW_HEIGHT/2 - 150
        ),
        30

    );
    renderButton(game::menu.getStartBtn());
    renderButton(game::menu.getNameField());
    renderButton(game::menu.getRandomNameBtn());
    if(fileSys::checkLevelFile()){
        renderButton(game::menu.getContinueBtn());
    }

    game::menu.renderScores();
}