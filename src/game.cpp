#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/game.hpp"

namespace game{

    int WINDOW_HEIGHT = 720;
    int WINDOW_WIDTH = 1200; 
    RenderWindow window("Game", WINDOW_WIDTH, WINDOW_HEIGHT); 

    bool gameRunning = true;

    Dimension lvlGrid(100,100);
    Dimension lvlDimension(lvlGrid.w*TILE_SIZE, lvlGrid.h*TILE_SIZE);
    

    int TILE_SIZE = 16;
    int SCALER = 2;

    //TEXTURES
    Textures textures(window);

    Player player(Vector2f(0, 0), textures.player);

    SDL_Rect camera = {0, 0, WINDOW_WIDTH/(SCALER), WINDOW_HEIGHT/(SCALER)};
}

void game::update(){

    player.update();
    cout 
    << "camer-w: " << camera.w 
    << " "
    << "cam-h :" << camera.h 
    << endl;

    //tile size is the same as the player pos
    camera.x = (player.getPos().x + TILE_SIZE/2)- WINDOW_WIDTH/(2*SCALER);
    camera.y = (player.getPos().y + TILE_SIZE/2)- WINDOW_HEIGHT/(2*SCALER);
    if(camera.x < 0)
        camera.x = 0;
    if(camera.y < 0)
        camera.y = 0;
    if(camera.x > lvlDimension.w - camera.w)
        camera.x = lvlDimension.w - camera.w;
    if(camera.y > lvlDimension.h - camera.h)
        camera.y = lvlDimension.w - camera.h;
   

    
    //cout<< "X:"<<player.getPos().x << "Y:" << player.getPos().y <<endl;
    

    
}