#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



#include "../include/timer.hpp"


Timer::Timer(){
    start = 0;
    end = 0;
    elapsed = 0.0f;
    elapsedMs = 0.0f;
    
    //4 physics 
    lastUpdate = SDL_GetTicks();
    current = 0;

    float deltaTime = 0;
}

void Timer::setStart(){
    start = SDL_GetPerformanceCounter();
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