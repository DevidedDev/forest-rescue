#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>



#include "../include/timer.hpp"


Timer::Timer(){
    start = 0;
    end = 0;
    elapsed = 0.0f;
    elapsedMs = 0.0f;
}

void Timer::setStart(){
    start = SDL_GetPerformanceCounter();
}

void Timer::setEnd(){
end = SDL_GetPerformanceCounter();
}

void Timer::update(){
    elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
    elapsedMs = (end - start) / (float)SDL_GetPerformanceFrequency();
    std::cout << "Current FPS: " << std::to_string(1.0f / elapsed) << std::endl;
}

void Timer::capFrames(){
    SDL_Delay(floor(16.666f - elapsedMs));

}