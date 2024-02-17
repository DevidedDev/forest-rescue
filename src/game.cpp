#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/game.hpp"
#include <iostream>
#include <vector>


    int game::WINDOW_HEIGHT = 720;
    int game::WINDOW_WIDTH = 1200; 
    RenderWindow game::window("Game", WINDOW_WIDTH, WINDOW_HEIGHT); 

    //Level level(1);

    Timer game::timer;

    float game::animatedFPS= 5.0f;

    bool game::gameRunning = true;

    float game::difficulty = 2;
    Level* game::level = new Level();

    //Dimension game::game::lvlDimension(20*TILE_SIZE, 20*TILE_SIZE);
    int game::TILE_SIZE = 16;
    int game::SCALER = 2;
    Dimension game::lvlDimension((game::level->getDimension().w)*game::TILE_SIZE, game::level->getDimension().h*game::TILE_SIZE);
    
    //TEXTURES
    Textures game::textures(window);
    

    Player game::player(Vector2f(0, 0), textures.player);

    SDL_Rect game::camera = {0, 0, WINDOW_WIDTH/(SCALER), WINDOW_HEIGHT/(SCALER)};
    


void game::update(){
    player.update();
    /*
    cout << game::lvlDimension.w << " "
    << game::lvlDimension.h << endl;
    */
    //tile size is the same as the player pos
    camera.x = (player.getPos().x + TILE_SIZE/2)- WINDOW_WIDTH/(2*SCALER);
    camera.y = (player.getPos().y + TILE_SIZE/2)- WINDOW_HEIGHT/(2*SCALER);
    if(camera.x < 0)
        camera.x = 0;
    if(camera.y < 0)
        camera.y = 0;
    if(camera.x > game::lvlDimension.w - camera.w)
        camera.x = game::lvlDimension.w - camera.w;
    if(camera.y > game::lvlDimension.h - camera.h)
        camera.y = game::lvlDimension.w - camera.h;
    
}