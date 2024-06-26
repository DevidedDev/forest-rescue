#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <list>
#include <vector>
#include "tribesman.hpp"
#include "math.hpp"
#include "files.hpp"

class Village{
private:
    int occupants;
    Vector2f location;
    Dimension dimension;
    std::list<Tribesman*> tribesmen;
    std::vector<Entity*> buildings;
public:
    Village(Vector2f p_location);
    Village(VillageData p_vil_data);
    ~Village();
    Village();
    Village(const Village& p_vil);
    void update();
    void render();
    std::list<Tribesman*>* getTribesmenList();
    VillageData getVillageData();

};