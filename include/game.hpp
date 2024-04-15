#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "render_window.hpp"
#include "player.hpp"
#include "textures.hpp"
#include "math.hpp"
#include "timer.hpp"
#include "level.hpp"
#include "text.hpp"

class game{
public:
    static int WINDOW_HEIGHT;
    static int WINDOW_WIDTH; 
    static RenderWindow window;
    static bool gameRunning;
    static Timer timer;
    static float animatedFPS;  
    static Dimension lvlGrid;
    static Dimension lvlDimension;
    static int TILE_SIZE;
    static int SCALER;
    static Textures textures;
    static TTF_Font *font;
    static Colors colors;
    static Player player;
    static SDL_Rect camera;
    static float difficulty;
    static Level* level;
    static int fireSpread;

    static void update();

};