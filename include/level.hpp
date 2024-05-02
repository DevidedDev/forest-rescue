// #pragma once

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

class Level
{
private:
   

    int allTiles;
    int burnedTiles;
    int maxEnemies;

    int villagesNum;

    int lastSpawn;
    int enemySpawnRate;


    int killCount;
    int killTarget;

    Timer timer;

    Dimension dimension;
    std::vector<std::vector<TileComp *>> tiles;
    std::list<Village *> villages;
    std::list<Enemy *> enemies;

public:
    Level();
    Level(LevelData p_data);
    ~Level();
    Level(const Level &p_lvl);
    Dimension getDimension();
    TileComp &getTile(Vector2f p_pos);
    void update();
    void render();
    void detectCollissions();
    void spawnEnemy();
    void setFire(Vector2f p_pos);
    bool checkLevelFinished();
    bool checkGameEnd();
    Timer &getTimer();
    int addPlayerScore();
    float getNonBurnedPercent();
    int &getLastSpawn();
    int &getKillCount();
    Village &getVillage(int p_i);
    Enemy &getEnemy(int p_i);
    int &getVillagesNum();
    int getEnemiesNum();
    void copyTileMap();
    void addEnemy(Vector2f& p_enemy);
    void addVillage(VillageData& p_vil_data);
    void addEnemyCount();
    void fireSpread(Vector2f tile_pos);

};

#endif // LEVEL_HPP