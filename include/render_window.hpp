#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "entity.hpp"
#include "player.hpp"
#include "text.hpp"


class RenderWindow{
    private:
        SDL_Window* window;
        SDL_Renderer *renderer;

        //TEXT STUFF
        SDL_Surface *textSurface;


        int mWidth;
        int mHeight;
        SDL_Color black;
        SDL_Texture* helloWorld;
        Text text;

    public:
        RenderWindow(const char *p_title, int p_widht, int p_heigth);
        SDL_Texture *loadTexture(const char *p_filePath);

        int getRefreshRate();

        void cleanUp();
        void clear();
        void render(Entity& p_ent); //pošlje po referenice
        void render(Player& p_ent);
        void display();

        //TEXT STUFF
       
        
        void drawNormalText();
        void blit(SDL_Texture *texture, int x, int y);

        //SDL_Renderer* getRenderer();

        void renderText(const char* p_text_val, SDL_Color p_color, Vector2f p_pos);
};