/*
#include <SDL2/SDL.h>
#include <iostream>

//using namespace std;

const int WIDTH = 1280;
const int HEIGTH = 720;

bool running = true;
 

int main (int argc, char** argv)
{
    

    while(running){

    }
    //cout << "Hello world";

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGTH,
        0
    );

    //set fulscreen
    //SDL_SetWindowFullscreen( window, SDL_WINDOW_FULLSCREEN );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    // Clear winow
    SDL_RenderClear( renderer );

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 100;
    r.h = 100;

    // Set render color to white
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255);

    // Render rect
    SDL_RenderFillRect( renderer, &r );

    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    // Wait for 5 sec
    SDL_Delay( 5000 );

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/