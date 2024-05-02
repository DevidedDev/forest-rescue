#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include "math.hpp"
#include "timer.hpp"
#include "tile_component.hpp"


struct Score{
    char name[25];
    int score;
    Score();
    Score(const char* name, int score);
};



namespace fileSys{
    void saveScore();
    void getScores(Score topScores[5]);
    void createScoreFile();
    void saveLevel();
    bool openLevel();
    bool checkLevelFile(); //does the level file exist?
    static const char *LVL_TILES_FILE_PATH = "../bin/tiles.bin";
    static const char *LVL_DATA_FILE_PATH = "../bin/level_data.bin";

    static const char *LVL_ENEMIES_FILE_PATH = "../bin/enemies.bin";
    static const char *LVL_VILLAGES_FILE_PATH = "../bin/villages.bin";

    static const char *SCORE_FILE_PATH = "../bin/scores.bin";

}



struct LevelData{
    Vector2f playerPos;
    int gameDifficulty;
    int playerScore;
    int lastSpawn;
    int killCount;
    Timer timer;

};

struct VillageData{
    Vector2f pos;
    Dimension dim;
    int villagersNum;
};

