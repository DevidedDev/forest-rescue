#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



#include "../include/timer.hpp"


Timer::Timer(){
    start = SDL_GetTicks();
    end = 0;
    elapsed = 0.0f;
    elapsedMs = 0.0f;

    
    //4 physics 
    lastUpdate =SDL_GetTicks();
    current = SDL_GetTicks();

    float deltaTime = 0;
}


Timer::Timer(const Timer& p_timer){
    start = SDL_GetTicks()- (p_timer.current - p_timer.start);
    end = 0;
    elapsed = 0.0f;
    elapsedMs = 0.0f;

    
    //4 physics 
    lastUpdate = SDL_GetTicks();
    current =  SDL_GetTicks();

    float deltaTime = 0;
}
void Timer::setStart(){
    start = SDL_GetTicks();
}

int Timer::getStart(){
    return start;
}

void Timer::setEnd(){
end = SDL_GetPerformanceCounter();
}

float Timer::getFps(){
    elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    return elapsed;
}

void Timer::capFrames(){
    elapsedMs = (end - start) / (float)SDL_GetPerformanceFrequency();
    SDL_Delay(floor(16.666f - elapsedMs));

}

//physics

void Timer::setCurent(){
    current = SDL_GetTicks();
}

int Timer::getCurent(){
    return current;
}

void Timer::setCurent(Timer& p_timer){
    current = p_timer.current;
}

void Timer::setLastUpdate(){
    lastUpdate = current;
}

void Timer::setDT(){
    deltaTime = (current - lastUpdate) / 1000.0f;
}

float Timer::getDT(){
    return deltaTime;
}

int Timer::getElapsed(){
    return (int)((current - start)/1000);
}

