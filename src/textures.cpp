#include "../include/textures.hpp"
#include "../include/render_window.hpp"
#include "../include/game.hpp"



Textures::Textures(RenderWindow& p_window){
    player = p_window.loadTexture("../res/gfx/player_texture.png");
    enemy = p_window.loadTexture("../res/gfx/enemy_texture.png");
    tribesmen  = p_window.loadTexture("../res/gfx/tribesmen_texture.png");
    grass = p_window.loadTexture("../res/gfx/grass_texture.png");
    water = p_window.loadTexture("../res/gfx/water_texture.png"); 
    trees = p_window.loadTexture("../res/gfx/trees_texture.png");
    fire = p_window.loadTexture("../res/gfx/fire_texture.png");
    village = p_window.loadTexture("../res/gfx/village_texture.png");


};