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
    

};