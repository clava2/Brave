#include "CTimer.h"

CTimer::CTimer()
{
    mStartTime = 0;
    mPausedTime = 0;
    mPaused = true;
}

Uint32 CTimer::getCurrentTick()
{
    return SDL_GetTicks() - mStartTime;
}

void CTimer::pause()
{
    mPaused = true;
}

void CTimer::stop()
{
    mPaused = true;
    mStartTime = 0;
}

void CTimer::start()
{
    mPaused = false;
    mStartTime = SDL_GetTicks();
}

bool CTimer::getShouldDraw()
{
    if((SDL_GetTicks() - mLastDrawTime) > mSleepTime)
    {
        mLastDrawTime = SDL_GetTicks();
        return true;
    }
    return false;
}

void CTimer::setFPS(int FPS)
{
    mSleepTime = 1.0/FPS;
}