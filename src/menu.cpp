#include "../include/menu.hpp"
#include "../include/textures.hpp"
#include "../include/game.hpp"
#include <iostream>
#include <fstream>
#include <time.h>

Button::Button(Vector2f p_pos,   char p_text[25], int p_textSize, SDL_Color p_color, SDL_Color p_background):
pos(p_pos), 
 textSize(p_textSize), 
color(p_color), background(p_background)

{  
    
    strcpy(text, p_text);
    
    TTF_Font *font = TTF_OpenFont("../res/dev/munro.ttf", textSize);

    if(font == NULL){
        std::cout << "Error: BUTTON FONT NOT OPEN" << std::endl;
    }


    // std::cout << "BUTTON:" << std::endl;
    //Get button size
    TTF_SizeText(font, text, &dim.w, &dim.h);
    TTF_CloseFont(font);
};

const char* Button::getTxt(){
    return text;
}

SDL_Color Button::getClr(){
    return color;
}


SDL_Color Button::getBg(){
    return background;
}

Dimension Button::getDim(){
    return dim;
}

Vector2f Button::getPos(){
    return pos;
}

int Button::getTxtSize(){
    return textSize;
}

void Button::setPos(Vector2f p_pos){
    pos = p_pos;
}

SDL_Rect Button::getRect(){
    SDL_Rect tmp;
    tmp.x = pos.x;
    tmp.y = pos.y;
    tmp.h = dim.h;
    tmp.w = dim.w;
    return tmp;
}




//TEXT FIELD

TextField::TextField(Vector2f p_pos, int width,  char p_text[25], int p_textSize, SDL_Color p_color, SDL_Color p_background)
:Button( p_pos,   p_text, p_textSize, p_color, p_background)
{   
    strcpy(text,"test");
    dim.w  = width;


}

void TextField::setRandomName(){
    std::cout << "function start" << std::endl;
    std::ifstream datai;
    datai.open("../bin/random_names.txt");
    if(datai.is_open()){
        int rand_n = rand()%200;
        std::string s;
        for(int i = 0; i < rand_n; i++, getline(datai, s)){}
        std::cout << "Loop finished" << std::endl;
        std::cout << "New name:" << s << std::endl;
        const char *tmp ;
        strcpy(text, s.c_str());
        std::cout << "string converted" << std::endl;
        //strcpy(text, tmp);
        std::cout << "name set" << std::endl;
    }else{
        std::cout << "Error: Unable to open random names file" << std::endl;
    }
    strcpy(game::playerName, text); 
    datai.close();

}

void TextField::changeState(){

    selected = !selected;
    
        strcpy(game::playerName, text); 
    
    //std::cout << "Selected:" << (selected? "YES": "NO") << std::endl;
}

void TextField::changeState(bool b){

    selected = b;
    std::cout << "Selected:" << (selected? "YES": "NO") << std::endl;
}


void TextField::removeChar(){
    if(selected){
        if(strlen(text) != 0){
            text[strlen(text)-1] = '\0';
        }
    }
    
}

void TextField::addChar(char p_c){
    if(selected){
        int len = strlen(text);
        if(len < 25)
        {
            text[len] = p_c;
            text[len+1] = '\0';

        }
    }
    strcpy(game::playerName, text);
}

//MENU

Menu::Menu()
:startBtn(
        Vector2f(
            game::WINDOW_WIDTH/2-100,
            game::WINDOW_HEIGHT/2
        ),
        
        "Start Game",
        100,
        Colors::black,
        Colors::white
    ),
    
   randomNameBtn(
        Vector2f(
            game::WINDOW_WIDTH/2 +  300,
            game::WINDOW_HEIGHT/2 - 50
        ),
       
        "Get Random Name",
        30,
        Colors::black,
        Colors::white 
   ),
   nameField(
        Vector2f(
            game::WINDOW_WIDTH/2 + 250,
            game::WINDOW_HEIGHT/2 - 100
        ),
        320,
        "",
        20,
        Colors::black,
        Colors::white 
   ),
   continueBtn(
        Vector2f(
            game::WINDOW_WIDTH/2,
            game::WINDOW_HEIGHT/2 + 150
        ),
       
        "Continue previous game",
        30,
        Colors::black,
        Colors::white 
   )

   
{
    startBtn.setPos(Vector2f(
        (game::WINDOW_WIDTH / 2) - (startBtn.getDim().w / 2 ),
        startBtn.getPos().y
        )
    );


    continueBtn.setPos(Vector2f(
        (game::WINDOW_WIDTH / 2) - (continueBtn.getDim().w / 2 ),
        continueBtn.getPos().y
        )
    );
    srand(time(NULL));
    nameField.setRandomName();
    fileSys::getScores(scores);

    strcpy(game::playerName, nameField.getTxt()); 
}


Button& Menu::getStartBtn(){

    return startBtn;
}

Button& Menu::getRandomNameBtn(){
    return randomNameBtn;
}

Button& Menu::getContinueBtn(){
    return continueBtn;
}

TextField& Menu::getNameField(){
    return nameField;
}


void Menu::renderScores(){
    for(int i = 0; i < 5; i++){
        char outputString[50];
        sprintf(outputString, "%d %s %s %s %d", i+1 , ".  ", scores[i].name, "  ", scores[i].score);

        game::window.renderText(
            outputString,
            Colors::black,
            Vector2f(
                30,
                game::WINDOW_HEIGHT/2 - 200 + 40*i
            ),
            30
        );
    }
}


void Menu::syncScore(){
    fileSys::getScores(scores);

}