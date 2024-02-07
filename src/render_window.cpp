#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/render_window.hpp"
#include "../include/entity.hpp"

using namespace std;


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
        cout << "Window failed to init. ERROR:" << SDL_GetError() << endl;
    }
    //creates renderer (window_to_render, use first ok graphics driver, use gpu if possible)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); 


}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer,     p_filePath);
    if (texture == NULL){
        cout << "Failed to load texture. error:" << SDL_GetError() << endl;
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

void RenderWindow::render(Entity& p_ent){ //
    // NULL src  & texture fills whole screen
    SDL_Rect src = p_ent.getCurrentFrame();  // SDL struktura
    /*
    src.x = 0;
    src.y = 0;
    src.w = 512;
    src.h = 512;
    */
    
    

    SDL_Rect dest;
    dest.x = p_ent.getPos().x *4;
    dest.y = p_ent.getPos().y * 4;
    dest.w = src.w * 4;
    dest.h = src.h * 4;
    

    SDL_RenderCopy(renderer, p_ent.getTex(), &src, &dest);
}

void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}