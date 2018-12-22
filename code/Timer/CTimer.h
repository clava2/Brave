#ifndef __TIMER__
#define __TIMER__

#include <SDL2/SDL.h>


class CTimer
{
    private:
    Uint32 mStartTime;
    Uint32 mPausedTime;

    Uint32 mLastDrawTime;

    bool mPaused;
    double mSleepTime;

    public:

    CTimer();
    void start();
    void pause();
    void stop();
    Uint32 getCurrentTick();
    void setFPS(int FPS);
    bool getShouldDraw();
};



#endif