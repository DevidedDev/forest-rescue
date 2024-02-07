#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"


class RenderWindow{
    private:
        SDL_Window* window;
        SDL_Renderer *renderer;
    public:
        RenderWindow(const char *p_title, int p_widht, int p_heigth);
        SDL_Texture *loadTexture(const char *p_filePath);

        int getRefreshRate();

        void cleanUp();
        void clear();
        void render(Entity& p_ent); //pošlje po referenice
        void display();


};