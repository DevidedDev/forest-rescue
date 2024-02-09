#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "render_window.hpp"
#include "player.hpp"
#include "textures.hpp"
#include "math.hpp"


namespace game{

    extern int WINDOW_HEIGHT;
    extern int WINDOW_WIDTH; 
    extern RenderWindow window; 

    extern Dimension lvlGrid;
    extern Dimension lvlDimension;

    extern int TILE_SIZE;
    extern int SCALER;

    extern bool gameRunning;

    //TEXTURES
    extern Textures textures;

    extern Player player;

    extern SDL_Rect camera;

    extern void update();

}