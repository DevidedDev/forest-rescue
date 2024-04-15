#include "../include/village.hpp"
#include "../include/game.hpp"
#include <iostream>
#include <time.h>


Village::Village(Vector2f p_location)
:location(p_location)
{

    dimension.w = game::difficulty+2;
    dimension. h = game::difficulty+2;

    if(location.x > game::lvlDimension.w - dimension.w){
        location.x = game::lvlDimension.w - dimension.w;
    }
    if(location.y > game::lvlDimension.h - dimension.h){
        location.y = game::lvlDimension.h - dimension.h;
    }

    occupants = rand()%1 + game::difficulty;

    //Create tribesmen
    for(int i = 0; i < occupants;i++ ){
        Tribesman* tmp = new Tribesman(location, dimension);
        tribesmen.push_back(tmp);
    }
    //create houses
    for(int i = 0; i < dimension.h;i++){
        for(int j = 0; j < dimension.w; j++){
            if(rand() % 5 == 0){ // 1 in 5 tiles is hosue
                Entity* tmp = new Entity
                (
                    Vector2f(location.x + j, 
                    location.y + i), 
                    game::textures.village, 
                    (rand()%4)
                );
                buildings.push_back(tmp);
            }
        }
    }
    //THERE WILL ALWAYS BE ATLEAT 1 BUILDING PER VILLAGE
    if(buildings.empty()){
                Entity* tmp = new Entity
                (
                    Vector2f(location.x + floor(dimension.w/2), 
                    location.y  + floor(dimension.h/2)), 
                    game::textures.village, 
                    (rand()%4)
                );
                buildings.push_back(tmp);
    }

    std::cout << "Village created" << std::endl;
    std::cout << "x" << location.x << std::endl;
    std::cout << "y" << location.y << std::endl;
}


Village::~Village() {
    for (Tribesman* tribesman : tribesmen) {
        delete tribesman;
    }
    tribesmen.clear(); // Clear the container after deleting all elements


    for(Entity* b : buildings){
        delete b;
    }
    buildings.clear();
    std::cout << "Village deleted" << std::endl;


}

void Village::update(){
    for(Entity* e: buildings){
        e->update();
    }

    for(Tribesman* t : tribesmen){
        t->update();
    }
}

void Village::render(){
    for(Entity* e: buildings){
        game::window.render(*e);
    }
    for(Tribesman* t : tribesmen){
        game::window.render(*t);
    }
}

std::list<Tribesman*>* Village::getTribesmenList(){
    return &tribesmen;
}