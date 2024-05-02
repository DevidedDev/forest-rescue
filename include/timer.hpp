#pragma once

class Timer{
private:
    //for frames



    int start;
    int end;
    float elapsed;
    float elapsedMs;

    //for physics
    int current;
    int lastUpdate;

    float deltaTime;

    
public:
    Timer();
    Timer(const Timer& p_timer);
    void setStart();
    void setEnd();
    
    int getStart();

    float getFps();
    
    void capFrames();

    //for physics
    void setCurent();
    int getCurent();
    void setCurent(Timer& p_timer);
    void setLastUpdate();

    void setDT();
    float getDT();
    int getElapsed(); //get time from start to current time

};

