#include "../include/files.hpp"
#include "../include/game.hpp"


#include <iostream>
#include <fstream>

//Struct score DEFAULT CONSTRUCTOR
Score::Score()
:name(""), score(0)
{}

Score::Score(const char* p_name, int p_score)
:score(p_score){
    strcpy(name, p_name);
}

void fileSys::createScoreFile(){
    std::ifstream datai;
    datai.open(SCORE_FILE_PATH, std::ios::binary );
    if(!datai.is_open()){
        std::ofstream datao;
        datao.open(SCORE_FILE_PATH, std::ios::binary);
        Score tmp;
        for(int i = 0; i < 5; i++){
            datao.write((char*)&tmp, sizeof(tmp));
        }
        std::cout << "Score file created" << std::endl;
        
        datao.close();
    }else{
        std::cout << "Scores file already exists" << std::endl;
    }
    datai.close();
    

}

void fileSys::saveScore(){
    std::ofstream datao;
    std::ifstream datai;
    Score p_score(game::playerName, game::playerScore);

    datao.open(SCORE_FILE_PATH, std::ios::binary | std::ios::ate| std::ios::in ) ;
    datai.open(SCORE_FILE_PATH, std::ios::binary);
    if(!datai.is_open() ){ //empty file
        std::cout << "Error: can not save score. No scores.bin file to write to" << std::endl;
        createScoreFile();

        
    }
    Score tmp;
    
        int i;
        bool newHighscore = false;
        
        for(i = 0; i<5; i++){
            datai.read((char*)&tmp, sizeof(tmp));

            if(p_score.score > tmp.score){
                newHighscore = true;
                break;
            }
        }

        if(!newHighscore){
            std::cout << "No new higschore" << std::endl;
            return;
        }


        //write your value
    if(i != 5){ //check if new value is smaller than other values
        datao.clear();
        datao.seekp(sizeof(Score)*i, std::ios::beg);
        std::cout << "Datao location:" << datao.tellp() << std::endl;
        datao.write((char*)&p_score, sizeof(Score));
        Score tmp2;
        for(i; i <5; i++){

            datai.read((char*)&tmp2, sizeof(Score));
            datao.write((char*)&tmp, sizeof(Score));
            tmp = tmp2;
        }

    }
    std::cout << "Score saved!" << std::endl;
    datai.close();
    datao.close();

    // Score testScore[5];
    // getScores(testScore);
    // for(Score s: testScore){
    //     std::cout << "Scores:" <<
    // }

    
}

void fileSys::getScores(Score topScores[5]){
    
    std::ifstream datai;
    datai.open(SCORE_FILE_PATH, std::ios::binary);
    if(datai.is_open()){
        int i;
        Score tmp;
        
        for(int i = 0;  i < 5; i++){
            
            datai.read((char*)&tmp, sizeof(tmp));

            topScores[i] = tmp;
        }
        
    }else{
        std::cout << "No scores exist yet." << std::endl;
    }
    datai.close();
    
}


//
void fileSys::saveLevel(){
    //game::level->syncWGameData();
    std::ofstream file_tiles;
    file_tiles.open(LVL_TILES_FILE_PATH , std::ios::binary);

    TileComp* tmp;
    std::cout << "TILES OPENED" <<std::endl;
    for(int i = 0; i < game::lvlGrid.h; i++){
        for(int j = 0; j < game::lvlGrid.w;j++){
            tmp = &game::level->getTile(Vector2f(j,i));
            file_tiles.write((char*)tmp, sizeof(TileComp));
        }
    }
    file_tiles.close();
    std::cout << "TILES SAVED" <<std::endl;
    //LEVEL DATA
    std::ofstream file_lvl_data;
    file_lvl_data.open(LVL_DATA_FILE_PATH , std::ios::binary);
    LevelData lvlData;
    lvlData.playerPos = game::player.getPos(); //game
    lvlData.gameDifficulty = game::difficulty;
    lvlData.playerScore = game::playerScore;
    lvlData.lastSpawn = game::level->getLastSpawn();
    lvlData.killCount = game::level->getKillCount();
    lvlData.timer = game::level->getTimer();
    file_lvl_data.write((char*)&lvlData, sizeof(LevelData));
    file_lvl_data.close();

    std::ofstream file_enemies_data;
    file_enemies_data.open(LVL_ENEMIES_FILE_PATH , std::ios::binary);
    std::cout << "LEVEL DATA SAVED" <<std::endl;
    Vector2f enemyPos;
    for(int i = 0; i < game::level->getEnemiesNum(); i++){
        enemyPos = game::level->getEnemy(i).getPos();
        file_enemies_data.write((char*)&enemyPos, sizeof(Vector2f));
        //code for saving village data

    }
     file_enemies_data.close();
    std::cout << "ENEMIES SAVED" <<std::endl;


    std::ofstream file_villages_data;
    VillageData vil_data;
    file_villages_data.open(LVL_VILLAGES_FILE_PATH , std::ios::binary);
    for(int i = 0; i < game::level->getVillagesNum(); i++){
        vil_data = game::level->getVillage(i).getVillageData();
        file_villages_data.write((char*)&vil_data, sizeof(VillageData));
    }
    file_villages_data.close();
    std::cout << "VILLAGES SAVED" <<std::endl;



}

bool fileSys::openLevel(){
    //game::level->syncWGameData();
    //LEVEL DATA
    std::ifstream file_lvl_data;
    file_lvl_data.open(LVL_DATA_FILE_PATH , std::ios::binary);
    if(!file_lvl_data.is_open()){
        std::cout << "Error: Unable to open level file data" << std::endl;
        return 0;
    }
    LevelData lvlData;
    file_lvl_data.read((char*)&lvlData, sizeof(LevelData));
    file_lvl_data.close();
    //SYNC DATA
    game::player.setPos(lvlData.playerPos);
    game::difficulty = lvlData.gameDifficulty;
    game::playerScore = lvlData.playerScore;
   
    //delete game::level;
    game::level = new Level(lvlData);

    //FILE TILES
    game::level->copyTileMap();

    //ENEMIES
    std::ifstream file_enemies_data;
    file_enemies_data.open(LVL_ENEMIES_FILE_PATH , std::ios::binary);
    if(!file_enemies_data.is_open()){
        std::cout << "Error: Unable to open level ENEMIES data" << std::endl;
        return 0;
    }
    std::cout << "ENEMIES OPENED" <<std::endl;
    Vector2f enemy_pos;
    
    while(file_enemies_data.read((char*)&enemy_pos, sizeof(Enemy))){
        enemy_pos = Vector2f(enemy_pos.x/16, enemy_pos.y/16);
        game::level->addEnemy(enemy_pos);
        std::cout << "Enemy ";
    }
    std::cout << std::endl;
    
    file_enemies_data.close();
    std::cout << "ENEMIES SAVED" <<std::endl;

    //VILLAGES
    std::ifstream file_villlages_data;
    file_villlages_data.open(LVL_VILLAGES_FILE_PATH , std::ios::binary);
    if(!file_villlages_data.is_open()){
        std::cout << "Error: Unable to open level villages data" << std::endl;
        return 0;
    }
    std::cout << "villages OPENED" <<std::endl;
    VillageData vil_data;
    while(file_villlages_data.read((char*)&vil_data, sizeof(VillageData))){
        game::level->addVillage(vil_data);
        std::cout << "Village ";
        //std::cout << " location: "<< &vil<< std::endl;

    }
    std::cout << std::endl;
    
    file_villlages_data.close();
    std::cout << "villages SAVED" <<std::endl;
    std::cout << "All Level data synced sucessfully" << std::endl;
    remove(LVL_DATA_FILE_PATH);
    remove(LVL_ENEMIES_FILE_PATH);
    remove(LVL_TILES_FILE_PATH);
    remove(LVL_VILLAGES_FILE_PATH);
    return 1;
}

bool fileSys::checkLevelFile(){
    std::ifstream datai;
    datai.open(LVL_TILES_FILE_PATH , std::ios::binary);
    bool is_open = datai.is_open();
    if(is_open){
        //std::cout << "FILE EXIST!" <<std::endl;
    }else{
        //std::cout << "FILE DOES NOT EXIST!" <<std::endl;
    }
    datai.close();
    return is_open;
}
