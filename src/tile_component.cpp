#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/tile_component.hpp"
#include "../include/textures.hpp"
#include "../include/game.hpp"


TileComp::TileComp(const Vector2f& p_pos)
:
tree(Entity(Vector2f(p_pos.x*16,p_pos.y*16), game::textures.trees, 0)),
grass(Entity(Vector2f(p_pos.x*16,p_pos.y*16), game::textures.grass, 0))
{   
    //std::cout << "tile grass: " << p_grassTex << std::endl;
    // std::cout << "pos " << p_pos.x<< " " 
    // << p_pos.y << endl;
    //p_pos.x *= game::TILE_SIZE;
    //p_pos.y *= game::TILE_SIZE;
    //std::cout << "Ent grass:" << game::textures.trees << std::endl;
    //std::cout << "Trees:" << treeTexture << std::endl;

}

TileComp::TileComp(){};
void TileComp::update(){
}

void TileComp::render(){
    game::window.render(grass);
    game::window.render(tree);
    // std::cout << tree.getPos().x << " " << 
    // tree.getPos().y << std::endl;
    //std::cout << "Rendering tile" << std::endl;
}

Entity* TileComp::getGrass(){
    return &grass;
}

Entity* TileComp::getTree(){
    return &tree;
}

  