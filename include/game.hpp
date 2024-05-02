#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstring>

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
    static Menu menu;
    static char gameTitle[20];
    static char mode[5];
    static bool gameRunning;
    static Timer timer;
    static float animatedFPS;  
    static Dimension lvlGrid;
    static Dimension lvlDimension;
    static int TILE_SIZE;
    static int SCALER;
    static Textures textures;
    static TTF_Font *font;
    static Player player;
    static SDL_Rect camera;
    static float difficulty;
    static Level* level;
    static int fireSpread;
    static int burnTime;
    static int playerScore;
    static char playerName[25];

    static void updateCam();
    static void update();
    static void addPlayerScore();
    static void resetLevel();
    static void finishGame();
};