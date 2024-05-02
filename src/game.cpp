#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../include/game.hpp"
#include <iostream>
#include <vector>


int game::WINDOW_HEIGHT = 720;
int game::WINDOW_WIDTH = 1200;
RenderWindow game::window("Game", WINDOW_WIDTH, WINDOW_HEIGHT);

Menu game::menu;

// Level level(1);
char game::gameTitle[20] = "Forest rescue";

Timer game::timer;

float game::animatedFPS = 5.0f;

bool game::gameRunning = true;

char game::mode[5] = "MENU"; // GAME, PAUSE

float game::difficulty = 1;

Level *game::level = nullptr;

// Dimension game::game::lvlDimension(20*TILE_SIZE, 20*TILE_SIZE);
int game::TILE_SIZE = 16;
int game::SCALER = 2;
// LVL DIMENSION IN PIXELS
Dimension game::lvlGrid ;
Dimension game::lvlDimension;

// TEXTURES
Textures game::textures(window);
// FONTS
TTF_Font *game::font = TTF_OpenFont("../res/dev/munro.ttf", 100);


Player game::player(textures.player);

SDL_Rect game::camera = {0, 0, WINDOW_WIDTH / (SCALER), WINDOW_HEIGHT / (SCALER)};

int game::fireSpread = 5000;

 int game::burnTime = 20000;

int game::playerScore  = 0;

char game::playerName[25];

void game::updateCam()
{
    camera.x = (player.getPos().x + TILE_SIZE / 2) - WINDOW_WIDTH / (2 * SCALER);
    camera.y = (player.getPos().y + TILE_SIZE / 2) - WINDOW_HEIGHT / (2 * SCALER);
    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > game::lvlDimension.w - camera.w)
        camera.x = game::lvlDimension.w - camera.w;
    if (camera.y > game::lvlDimension.h - camera.h)
        camera.y = game::lvlDimension.h - camera.h;
}

void game::update()
{

    if (!strcmp(game::mode, "MENU"))
    {
        timer.getCurent();
        window.renderMenu();
        game::window.renderText(
            gameTitle,
            Colors::white,
            Vector2f
            (
               ( WINDOW_WIDTH / 2 ) -250 , (WINDOW_HEIGHT / 2 ) - 300
            ),
            100
        );
    }
    else if (!strcmp(game::mode, "GAME"))
    {
        // std::cout << "UPDATING GAME" << std::endl;
        player.update();
        // std::cout <<"Player updated" <<std::endl;
        level->detectCollissions();
        // std::cout <<"Collisions checked" << std::endl;
        level->spawnEnemy();
        // std::cout <<"enemy spawned checkd" <<std::endl;
        level->render();
        // std::cout <<"level rendered checked" <<std::endl;
        window.render(game::player);
        // std::cout <<"player rendered checked" <<std::endl;
        updateCam();
        // std::cout <<"Camera updated checked" <<std::endl;
    }
    else if (!strcmp(game::mode, "PAUSE"))
    {
    }
    else
    {
        std::cout << "Error: No suitable mode!" << std::endl;
    }
}


void game::addPlayerScore(){
    playerScore += 100
    * 
    (difficulty*120 / game::level->getTimer().getElapsed() )
    *
    level->getNonBurnedPercent();
    std:: cout << "player score updated: " << playerScore << std::endl;
}

void game::resetLevel(){
    game::difficulty= 1;
    game::playerScore  = 0;
    //delete game::level;
    game::level = new Level();

}

void game::finishGame(){
    fileSys::saveScore();
    strcpy(game::mode, "MENU");
    game::menu.syncScore();

    
}