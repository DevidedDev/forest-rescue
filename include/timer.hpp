#pragma once

class Timer{
private:
    int ticks;

    int start;
    int end;
    float elapsed;
    float elapsedMs;
public:
    Timer();
    void setStart();
    void setEnd();
    void update();
    void capFrames();

};