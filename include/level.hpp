//#pragma once

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <list>

#include "village.hpp"
#include "tile_component.hpp"
#include "math.hpp"
#include "enemy.hpp"

class Level{
private:
    int allTiles;
    int burnedTiles;

    int villagesNum;
    int enemiesNum;

    int lastSpawn;
    int enemySpawnRate;

    int fireSpread;

    int killCount;
    int killTarget;

    Dimension dimension;
    std::vector<std::vector<TileComp*>> tiles;
    std::list<Village*> villages;
    std::list<Enemy*> enemies;

public:
    Level();
    ~Level();
    Level(const Level& p_lvl);
    Dimension getDimension();
    TileComp& getTile(Vector2f p_pos);
    void update();
    void render();
    void detectCollissions();
    void spawnEnemy();
    void setFire(Vector2f p_pos);
    bool checkLevelFinished();
    bool checkGameEnd();
};


#endif //LEVEL_HPP