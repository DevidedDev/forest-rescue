#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "files.hpp"
#include "math.hpp"

class Button
{
protected:
    Vector2f pos;
    Dimension dim;
    char text[25];
    int textSize;
    SDL_Color color;
    SDL_Color background;
    

public:
    Button(
        Vector2f p_pos,
        char p_text[25], int TextSize ,
        SDL_Color p_color, SDL_Color p_background
    );
    const char *getTxt();
    SDL_Color getClr();
    SDL_Color getBg();
    Vector2f getPos();
    Dimension getDim();
    int getTxtSize();
    void setPos(Vector2f p_pos);
    SDL_Rect getRect();

};

//TEXT FIELD
class TextField : public Button
{
private:
    bool selected;

public:
   TextField(
        Vector2f p_pos,
        int width,
        char p_text[25], int TextSize ,
        SDL_Color p_color, SDL_Color p_background
    );
    void setRandomName();
    void changeState(); //can you write or not?
    void changeState(bool b);
    void addChar(char p_c);
    void removeChar();
};


//MENU
class Menu
{
private:
    Score scores[5];
    Button startBtn;
    Button randomNameBtn;
    Button continueBtn;
    TextField nameField;
public:
    Menu();
    TextField& getNameField();
    Button& getStartBtn();
    Button& getRandomNameBtn();
    Button& getContinueBtn();
    void renderScores();
    void syncScore(); //sync with scores of actual files
};