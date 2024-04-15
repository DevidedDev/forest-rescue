#include "../include/level.hpp"
#include "../include/game.hpp"

#include <vector>
#include <list>
#include <iostream>
#include <time.h>
#include <string.h>

Level::Level()
{   
    burnedTiles= 0;
    TileComp::resetBurnedTilesNum();
    

    game::difficulty += 1;
    killCount = 1;
    killTarget = 5*game::difficulty;
    dimension.h = floor(20*game::difficulty);
    dimension.w = floor(20*game::difficulty);

    game::lvlGrid = getDimension();
    game::lvlDimension = Dimension(
        (getDimension().w)*game::TILE_SIZE,
        getDimension().h*game::TILE_SIZE
    );

    allTiles = dimension.h * dimension.w;
    //std::cout << dimension.w << " " <<dimension.w << std::endl;
    for(int i = 0; i < dimension.h; i++){
        std::vector<TileComp*>vec;
        tiles.push_back(vec);
        for(int j = 0; j < dimension.w;j++){
            TileComp* tmp = new TileComp(Vector2f(i,j));
            tiles[i].push_back(tmp);
            //std::cout << tiles[i].size() << std::endl;
        }
        //std::cout << &tiles[i] << std::endl;
    }

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

    enemiesNum = game::difficulty + rand()%2;
    enemySpawnRate = 20000;

    //CREATE ENEMIES
    for(int i = 0; i < enemiesNum; ++i){
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

Dimension Level::getDimension(){
    return dimension;
}

TileComp& Level::getTile(Vector2f p_pos){
    return *tiles[p_pos.x][p_pos.y];
}

void Level::render(){
  // cout << "Update tile" << endl;
    for(int i = 0; i < dimension.w; i++){
        for(int j = 0; j < tiles[i].size();j++){
        tiles[i][j]->update();
        tiles[i][j]->renderGrass();

        //SPREAD
        if(
            tiles[i][j]->getIsBurning()
            &&
            (game::timer.getCurent() - tiles[i][j]->getFire().getLastSpread() ) > game::fireSpread
            // &&
            // tiles[i][j]->getLastTimeBurned() > game::fireSpread
        ){
            tiles[i][j]->getFire().setLastSpread();
            Vector2f fireDirection;
            
            //CHECK IT GOES OUTSIDE OF MAP
                int tmp = 0;
                tmp = rand()%4;
                switch (tmp)
                {
                case 0:
                    if(i != 0)
                    tiles[i-1][j]->startBurning();
                    break;
                case 1:
                    if(i != this-> dimension.w-1)
                    tiles[i+1][j]->startBurning();
                    break;

                case 2:
                    if(j != this-> dimension.w-1)
                    tiles[i][j+1]->startBurning();
                    break;

                case 3:
                    if(j != 0)
                    tiles[i][j-1]->startBurning();
                    break;

                default:
                std::cout<< "Invalid burn spread direction" << std::endl;
                    break;
                }
            
        }

        // Entity *tree = (*tiles[i][j]).getTree();
        // Entity *grass = (*tiles[i][j]).getGrass();
        // game::window.render(*grass);
        // game::window.render(*tree);
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
    for(int i = 0; i < dimension.w; i++){
        for(int j = 0; j < tiles[i].size();j++){
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
        game::colors.white, 
        Vector2f
        (
           0,0
        )
    );
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
            game::gameRunning = false;
            
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
    enemiesNum > enemies.size()
    ){
    Vector2f enymPos;
    enymPos.x = rand() % (dimension.w);
    enymPos.y = rand() % (dimension.h);
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
    getTile(p_pos).startBurning();
}

bool Level::checkLevelFinished(){
    
    if(killCount >= killTarget
    
    ){
        return true;
    }
    return false;

}


bool Level::checkGameEnd(){
    std::cout << TileComp::burnedTilesNum/allTiles << std::endl;
    return TileComp::burnedTilesNum/allTiles >= 0.7;
}