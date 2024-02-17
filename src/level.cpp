#include "../include/level.hpp"
#include "../include/game.hpp"

#include <vector>
#include <iostream>

Level::Level()
{
    dimension.h = floor(20*game::difficulty);
    dimension.w = floor(20*game::difficulty);
    
    std::cout << "HELLO" << std::endl;
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
    std::cout << "level removed" << std::endl;
}

Dimension Level::getDimension(){
    return dimension;
}

TileComp Level::getTile(int p_x, int p_y){
    //return tiles[p_x][p_y];
}

void Level::render(){
  // cout << "Update tile" << endl;
    for(int i = 0; i < dimension.w; i++){
        for(int j = 0; j < tiles[i].size();j++){
        Entity *tree = (*tiles[i][j]).getTree();
        Entity *grass = (*tiles[i][j]).getGrass();

        game::window.render(grass);
        game::window.render(tree);
        //std::cout << grass << std::endl;
        }
        int tmp;
        //std::cout << &tiles[i] << std::endl;
        //std::cin >> tmp;
    }
    // std::cout << "level rendered" << std::endl;
}