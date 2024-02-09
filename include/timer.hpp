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
    void setStart();
    void setEnd();

    float getFps();
    
    void capFrames();

    //for physics
    void setCurent();
    void setLastUpdate();

    void setDT();
    float getDT();
    

};