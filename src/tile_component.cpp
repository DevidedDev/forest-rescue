#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/tile_component.hpp"
#include "../include/textures.hpp"
#include "../include/game.hpp"

int TileComp::burnedTilesNum = 0 ;

TileComp::TileComp(const Vector2f& p_pos)
:
tree(Entity(p_pos, game::textures.trees, rand()%6)),
grass(Entity(p_pos, game::textures.grass, rand()%5)),
fire(Vector2f(p_pos.x, p_pos.y))
{
    isBurning = false;
    isBurned = false;
    lastTimeBurned  = 0;
}

TileComp::TileComp( TileComp& p_tile)
:
tree(Entity(
    Vector2f(
        p_tile.tree.getPos().x/16,
        p_tile.tree.getPos().y/16
    ),
    game::textures.trees, p_tile.tree.getCurrentFrame().x)
),
grass(Entity(
    Vector2f(
        p_tile.tree.getPos().x/16,
        p_tile.tree.getPos().y/16
    ), game::textures.grass, 
    Vector2f(
        p_tile.grass.getCurrentFrame().x,
        p_tile.grass.getCurrentFrame().y
    )
)
    
),
fire(p_tile.fire)
{
    isBurning = p_tile.isBurning;
    isBurned = p_tile.isBurned;
    lastTimeBurned  = game::level->getTimer().getCurent(); //fix timer
}



TileComp::TileComp()
:
tree(Entity(Vector2f(0,0), game::textures.trees, rand()%6)),
grass(Entity(Vector2f(0,0), game::textures.grass, rand()%5)),
fire(Vector2f(0,0))
{
    isBurning = false;
    isBurned = false;
    lastTimeBurned  = 0;
}


void TileComp::update(){
    if(game::level == NULL){
        std::cout << "level is null" << std::endl;
        return;
    }else{
        //std::cout << this <<std::endl;    
    }
    grass.update();
    tree.update();
    
    render();
    if(isBurning){
        fire.update();
        // std::cout << "I AM BURNING" << std::endl;
        
        if(fire.putOut()){
            isBurning  = false;
            lastTimeBurned = game::timer.getCurent();
        }
        //if tilesave gets fully burned down
        if(fire.destroyTile()){
            isBurning = false;
            isBurned = true;
            grass.updateFramePos(Vector2f(0,1));

            burnedTilesNum+=1;
            //std::cout << "Burned tiles" << burnedTilesNum << std::endl;
        }
    }
   
}

void TileComp::render(){
    if(game::level == NULL){
        std::cout << "Level p* is null" << std::endl;
        return;
    }else{
        //std::cout << this <<std::endl;    
    }
    game::window.render(grass);

    if(!isBurned){
        if(!game::player.isInVisibleRange(tree)){
            game::window.render(tree);
        }

    }

    
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

void TileComp::startBurning(){
    if((!isBurning) && (!isBurned) && (game::timer.getCurent() )  ){
        isBurning = true;
        fire.setLastSpread();
    }
}
  
bool TileComp::getIsBurning(){
    return isBurning;

}

bool TileComp::getIsBurned(){
    return isBurned;
}

Fire& TileComp::getFire(){
    return fire;
}

int TileComp::getLastTimeBurned(){
    return lastTimeBurned;
}

void TileComp::renderGrass(){
    game::window.render(grass);
}
void TileComp::renderTree(){
    game::window.render(tree);
}

void TileComp::renderFire(){
    game::window.render(fire);
}

void TileComp::resetBurnedTilesNum(){
    burnedTilesNum = 0;
}

int TileComp::getBurnedTilesNum(){
    return burnedTilesNum;
}