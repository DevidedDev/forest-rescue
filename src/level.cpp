#include "../include/level.hpp"
#include "../include/game.hpp"

#include <vector>
#include <list>
#include <iostream>
#include <time.h>
#include <string.h>

Level::Level()
{   
    TileComp::resetBurnedTilesNum();
    timer.setStart();
    
    timer.setLastUpdate();

    //game::difficulty += 1;
    killCount = 0;
    killTarget = 1 + 2*game::difficulty;
    dimension.h = floor(21 + game::difficulty * 2.5 );
    dimension.w = floor(36+ game::difficulty * 2.5);
    
    game::lvlGrid = getDimension(); //in tiles
    game::lvlDimension = Dimension( //in pixels
        (getDimension().w)*game::TILE_SIZE,
        getDimension().h*game::TILE_SIZE
    );


    game::player.setPos(Vector2f(
        rand()%dimension.w *game::TILE_SIZE,
        rand()%dimension.h *game::TILE_SIZE
        )
    );

    allTiles = dimension.h * dimension.w;
    //std::cout << dimension.w << " " <<dimension.w << std::endl;

    for(int i = 0; i < dimension.h; i++){
        std::vector<TileComp*>vec;
        tiles.push_back(vec);
        for(int j = 0; j < dimension.w;j++){
            TileComp* tmp = new TileComp(Vector2f(j,i));
            tiles[i].push_back(tmp);
            //std::cout << tiles[i].size() << std::endl;
        }
        //std::cout << &tiles[i] << std::endl;
    }
        std::cout << "loaded" << std::endl;

    villagesNum = game::difficulty+1;
    //CREATE VILLAGES
    for(int i = 0; i < villagesNum; i++)
    {
        Village* vil = new Village(
            Vector2f(
                rand()%getDimension().w,
                rand()%getDimension().h
                
            )
        );
        villages.push_back(vil);
    }

    maxEnemies = game::difficulty + rand()%2;
    enemySpawnRate = 20000;

    //CREATE ENEMIES
    for(int i = 0; i < maxEnemies; ++i){
        Enemy* tmp = new Enemy(
            Vector2f
            (
                rand() % dimension.w,
                rand() % dimension.h
                
            )
        );
        enemies.push_back(tmp);
    }

    lastSpawn = game::timer.getCurent();


    std::cout << "level created" << std::endl;

}

Level::Level(const Level& p_lvl)
:timer(p_lvl.timer), dimension(p_lvl.dimension) , tiles(p_lvl.tiles), villages(p_lvl.villages), enemies(p_lvl.enemies)
{

     allTiles = p_lvl.allTiles;
     burnedTiles = burnedTiles;

     villagesNum = p_lvl.villagesNum;
     maxEnemies = p_lvl.maxEnemies;

     lastSpawn = p_lvl.lastSpawn;
     enemySpawnRate = p_lvl.enemySpawnRate;


     killCount = p_lvl.killCount;
     killTarget = p_lvl.killTarget;


}


Level::~Level(){
    for(int i = 0; i < dimension.h; i++){
        for(int j = 0; j < dimension.w;j++){
            delete tiles[i][j];
            tiles[i][j] = nullptr;
        }
    }

        tiles.clear();

    //deletes villages
    for(Village* vil : villages){
        delete vil;
    }
    villages.clear();

    //delete enemies
    for(Enemy* e : enemies){
        delete e;
    }
    enemies.clear();

    std::cout << "level removed" << std::endl;
}

Level::Level(LevelData p_data)
:timer(p_data.timer)
{
    TileComp::resetBurnedTilesNum();
    lastSpawn = p_data.lastSpawn;
    killCount = p_data.killCount;


   
    
    killTarget = 1 + 2*game::difficulty;
    dimension.h = floor(21 + game::difficulty * 2.5 );
    dimension.w = floor(36+ game::difficulty * 2.5);

    game::lvlGrid = getDimension(); //in tiles
    game::lvlDimension = Dimension( //in pixels
        (getDimension().w)*game::TILE_SIZE,
        getDimension().h*game::TILE_SIZE
    );

    allTiles = dimension.h * dimension.w;

    villagesNum = game::difficulty+1;

    maxEnemies = game::difficulty + rand()%2;
    enemySpawnRate = 20000;

    lastSpawn = game::timer.getCurent();

    std::cout << "level recreated" << std::endl;
}

Dimension Level::getDimension(){
    return dimension;
}

TileComp& Level::getTile(Vector2f p_pos){
    return *tiles[p_pos.y][p_pos.x];
}

void Level::render(){
  // cout << "Update tile" << endl;
        game::timer.setCurent();

    for(int i = 0; i < dimension.h; i++){
        for(int j = 0; j < dimension.w;j++){
        tiles[i][j]->update();
        tiles[i][j]->renderGrass();

        //SPREAD
        fireSpread(Vector2f (j,i));

        }
        
    }
    //RENDER VILAGES
    for(Village* v : villages){
        v->update();
        v->render();
    }

    //RENDER ENEMIES  & UPDATE ENEMIES
    for(Enemy* e: enemies){
         if(e->isIdle()){
            Vector2f tmp = e->getTilePos();
            setFire(tmp);
        }
        e->update();
        game::window.render(*e);
    }
    //RENDER TREES &&FIRE
    for(int i = 0; i < dimension.h; i++){
        for(int j = 0; j < dimension.w;j++){
        if(!tiles[i][j]->getIsBurned()){
        if(!game::player.isInVisibleRange(*tiles[i][j]->getTree())){
            tiles[i][j]-> renderTree();
        }
        if(tiles[i][j]->getIsBurning()){
            tiles[i][j]->renderFire();
        }



        }
        
        }
    }
    char outputString[40];
    
     sprintf(outputString, "%s %d %s %d", "Kill count: ", killCount, "  / ", killTarget);

    game::window.renderText(
        outputString, 
        Colors::white, 
        Vector2f
        (
           0,0
        ),
        40
    );

    timer.setCurent();
    sprintf(outputString, "%s %d", "Time: ", timer.getElapsed());

    game::window.renderText(
        outputString,
        Colors::white,
        Vector2f(0, 50),
        30
    );

    sprintf(outputString, "%s %d", "Score: ", game::playerScore);
    game::window.renderText(
        outputString,
        Colors::white,
        Vector2f(0, 90),
        30
    );

    game::window.renderText(
        game::playerName,
        Colors::white,
        Vector2f(game::WINDOW_WIDTH - 300, 50),
        30
    );
    //std::cout << game::playerName << std::endl;
}
void Level::detectCollissions(){
    int enemyColissions = 0;
    int visibleEnemies = 0;

    for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
    {
        if((*it)->detectCollision(game::player)){
            enemyColissions++;
        }
        if(game::player.isInVisibleRange(**it)){
            visibleEnemies++;
            //ENEMIES NOT MASHING UP
            // for(std::list<Enemy*>::iterator it_in = enemies.begin(); it_in != enemies.end(); it++){
            //     std::cout <<"checking for enemies close by " << std::endl;
            //     if(it_in != it){
                
            //         // (*it)->detectCollision(**it_in);
            //         //  (**it).setVelocityX(0);
            //         //  (**it).setVelocityY(0);
            //         break;
            //     }
            // }
        }
        
    }
    int visibleFriends = 0;
    if(enemyColissions >= 1){

        if(visibleEnemies > 1){
            for(Village* vil: villages){
                for(Tribesman* t : *(vil->getTribesmenList())){
                    if(game::player.isInVisibleRange(*t)){
                        visibleFriends++;
                    }
                }
            }
        }
        
        //if more enemies than tribesmen and player
        //then die
        if(visibleEnemies > visibleFriends + 1
        
        ){
            //KILL PLAYER

            //game::gameRunning = false;
            game::finishGame();
            
        }else{
            std::cout << "deleting enemies" << std::endl;
            for (std::list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ) {
                if ((*it)->detectCollision(game::player)) {
                    std::cout << "enemy being deleted" << std::endl;
                    killCount++;
                    delete *it;
                    
                    it = enemies.erase(it); // erase returns the iterator to the next valid position
                    std::cout << "enemy deleted" << std::endl;
                }else{
                    ++it; // move to the next element
                }
            }
        }


    }

    

}


void Level::spawnEnemy(){
    if(
    game::timer.getCurent() - lastSpawn >= enemySpawnRate
    &&
    maxEnemies > enemies.size()
    ){
    Vector2f enymPos;
    enymPos.y = rand() % (dimension.h);
    enymPos.x = rand() % (dimension.w);
    
    Enemy* tmp = new Enemy(
            Vector2f
            (
                enymPos.x,
                enymPos.y
            )
    );
    enemies.push_back(tmp);
    }
}


void Level::setFire(Vector2f p_pos){
    //std::cout << "Fire set" << std::endl;
    (*tiles[p_pos.y][p_pos.x]).startBurning();
}

bool Level::checkLevelFinished(){
    
    if(killCount >= killTarget
    
    ){
        return true;
    }
    return false;

}


bool Level::checkGameEnd(){
    
    return (float(TileComp::burnedTilesNum)/float(allTiles) >= 0.7);
}

Timer& Level::getTimer(){
    return timer;
}

float Level::getNonBurnedPercent(){
    return (1- float(TileComp::burnedTilesNum)/float(allTiles));
}

int &Level::getLastSpawn(){
    return lastSpawn;
}

int &Level::getKillCount(){
return killCount;
}

// Village Level::getVillage(int p_i){
//     std::list<Village*>::iterator it = villages.begin(); 
//     advance(it, 5); 

//     return it;
// };
Village& Level::getVillage(int p_i){
    if(p_i > villagesNum){
        std::cout << "Unable to fetch village, out of bounds" << std::endl;
    }
    std::list<Village*>::iterator it;
    it = villages.begin();
    for( int i = 0 ; i < p_i; ++it, ++i){
    }
    return **it;
};
Enemy& Level::getEnemy(int p_i){
    if(p_i > getEnemiesNum()){
        std::cout << "Unable to fetch enemy, out of bounds" << std::endl;
    }
    std::list<Enemy*>::iterator it;
    it = enemies.begin();
    for( int i = 0 ; i < p_i; ++it, ++i){
    }
    return **it;
};

int& Level::getVillagesNum(){
    return villagesNum;
}

int  Level::getEnemiesNum(){
    return enemies.size();
}

void Level::copyTileMap(){
    std::ifstream file_tiles;
    file_tiles.open(fileSys::LVL_TILES_FILE_PATH , std::ios::binary);
    TileComp tmp;
    TileComp* newTile;
    if(!file_tiles.is_open()){
        std::cout << "Error: Unable to copy tile map" << std::endl;
    }

    for(int i = 0; i < dimension.h; i++){
        std::vector<TileComp*>vec;

        tiles.push_back(vec);
        for(int j = 0; j < dimension.w;j++){
            file_tiles.read((char*)&tmp, sizeof(TileComp));
            newTile = new TileComp(tmp);
            
            tiles[i].push_back(newTile);
            //std::cout << "Tiles:" <<i << " " <<j <<std::endl;
            //std::cout << tiles[i].size() << std::endl;
        }
        //std::cout << &tiles[i] << std::endl;
    }
    std::cout << "TILES SAVED" <<std::endl;
    file_tiles.close();
}

void Level::addEnemy(Vector2f& p_pos){
    Enemy* enemy = new Enemy(p_pos);
    enemies.push_back(enemy);
    std::cout << "Enemy location: "<< &enemy << std::endl;

}

void Level::addVillage(VillageData& p_vil_data){
    Village* vil = new Village(p_vil_data);
    villages.push_back(vil);
}

void Level::fireSpread(Vector2f tile_pos){
     // std::cout << tile_pos.x << " "  << tile_pos.y<< ": " <<tiles[tile_pos.y][tile_pos.x]->getFire().getLastSpread() << std::endl;
    if((game::timer.getCurent() - tiles[tile_pos.y][tile_pos.x]->getFire().getLastSpread() ) > game::fireSpread){
      //  std::cout << "time to spread" << std::endl;
    }
    if(
        tiles[tile_pos.y][tile_pos.x]->getIsBurning()
        &&
        (game::timer.getCurent() - tiles[tile_pos.y][tile_pos.x]->getFire().getLastSpread() ) > game::fireSpread
        // &&
        // tiles[i][j]->getLastTimeBurned() > game::fireSpread
    ){
        tiles[tile_pos.y][tile_pos.x]->getFire().setLastSpread();
    
        //CHECK IT GOES OUTSIDE OF MAP
        int tmp = 0;
        tmp = rand()%4;
        switch (tmp)
        {
        case 0:
            if(tile_pos.y != 0)
                tiles[tile_pos.y -1][tile_pos.x]->startBurning();
            break;
        case 1:
            if(tile_pos.y  != this-> dimension.h-1)
                tiles[tile_pos.y +1][tile_pos.x]->startBurning();
            break;
        case 2:
            if(tile_pos.x != this-> dimension.w-1)
                tiles[tile_pos.y ][tile_pos.x+1]->startBurning();
            break;
        case 3:
            if(tile_pos.x != 0)
                tiles[tile_pos.y ][tile_pos.x-1]->startBurning();
            break;
        default:
        std::cout<< "Invalid burn spread direction" << std::endl;
            break;
        }
    }
        
}

