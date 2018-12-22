#include "CGame.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

CGame::CGame(bool init):mMainLog(log4cpp::Category::getRoot())
{
    mLogFileName = "../log4cpp.properities";
    log4cpp::PropertyConfigurator::configure(mLogFileName);
    int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
    if(errorCode)
    {
        mMainLog.error("Can not initialize SDL!");
    }
}

bool CGame::initState()
{
    mWindow = SDL_CreateWindow("Gaming",0,0,100,100,SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(mWindow == NULL)
    {
        mMainLog.error("Can not create window");
        return false;
    }
    SDL_GetWindowSize(mWindow,&mWindowWidth,&mWindowHeight);
    mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED);
    if(mRenderer == NULL)
    {
        mMainLog.error("Can not create renderer");
        return false;
    }
    SDL_SetRenderDrawColor(mRenderer,0x00,0xff,0xff,0x00);
    mQuitGame = false;
    mShouldRedraw = true;
    mState = GAME_STATE_START_PAGE;
    mMainMenuOption = MAIN_MENU_OPTION_START;
    mResumeMenuOption= RESUME_MENU_OPTION_RESUME;



    mStartPageInfo.startPageFileName = "../resources/pictures/start_page.jpg";
    mStartPageInfo.startPageTime = 2000;

    mMainTimer.start();
    mMainTimer.setFPS(60);

    return true;
}

bool CGame::loadMedia()
{
    SDL_Surface* tempSurface = IMG_Load(mStartPageInfo.startPageFileName.c_str());
    if(tempSurface == NULL)
    {
        mMainLog.warn("Can not load start_page.png");
    }
    mStartPageInfo.startPageTexture = SDL_CreateTextureFromSurface(mRenderer,tempSurface);
    if(mStartPageInfo.startPageTexture == NULL)
    {
        mMainLog.warn(string("can not create start page texture from surface")+SDL_GetError());
    }
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;
}

void CGame::mainLoop()
{
    SDL_Event event;
    
    while(!mQuitGame)
    {
        SDL_PollEvent(&event);
        handleInput(event);
        mShouldRedraw = updateData()&&(mMainTimer.getShouldDraw());
        if(mShouldRedraw)
        {
            SDL_RenderClear(mRenderer);
            redraw();
            SDL_RenderPresent(mRenderer);
        }
    }
}

void CGame::handleInput(SDL_Event& event)
{
    switch(mState)
    {
        case GAME_STATE_START_PAGE:
        startPageInput(event);
        return;
        case GAME_STATE_MAIN_MENU:
        mainMenuInput(event);
        break;
        case GAME_STATE_RESUME_MENU:
        resumeInput(event);
        break;
        case GAME_STATE_GAMING:
        gamingInput(event);
        break;
        case GAME_STATE_COMPLETE:
        completeInput(event);
        break;
    }
}
void CGame::startPageInput(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    mQuitGame = true;
                }
            }
        }
    }
    return;
}
void CGame::mainMenuInput(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    mQuitGame = true;
                }
            }
        }
    }
    return;
}
void CGame::resumeInput(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    mQuitGame = true;
                }
            }
        }
    }
    return;
}
void CGame::gamingInput(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    mQuitGame = true;
                }
            }
        }
    }
    return;
}
void CGame::completeInput(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    mQuitGame = true;
                }
            }
        }
    }
    return;
}

bool CGame::updateData()
{
    switch(mState)
    {
        case GAME_STATE_START_PAGE:
        return startPageUpdateData();
        case GAME_STATE_MAIN_MENU:
        return mainMenuUpdateData();
        case GAME_STATE_RESUME_MENU:
        return resumeUpdateData();
        case GAME_STATE_GAMING:
        return gamingUpdateData();
        case GAME_STATE_COMPLETE:
        return completeUpdateData();
    }
}
bool CGame::startPageUpdateData()
{
    if(mMainTimer.getCurrentTick()>mStartPageInfo.startPageTime)
    {
        mState = GAME_STATE_MAIN_MENU;
    }
    return true;
}
bool CGame::mainMenuUpdateData()
{
    return true;
}
bool CGame::resumeUpdateData()
{
    return true;
}
bool CGame::gamingUpdateData()
{
    return true;
}
bool CGame::completeUpdateData()
{
    return true;
}

void CGame::redraw()
{
    switch(mState)
    {
        case GAME_STATE_START_PAGE:
        startPageRedraw();
        return;
        case GAME_STATE_MAIN_MENU:
        mainMenuRedraw();
        break;
        case GAME_STATE_RESUME_MENU:
        resumeRedraw();
        break;
        case GAME_STATE_GAMING:
        gamingRedraw();
        break;
        case GAME_STATE_COMPLETE:
        completeRedraw();
        break;
    }
}
void CGame::startPageRedraw()
{
    SDL_RenderCopy(mRenderer,mStartPageInfo.startPageTexture,NULL,NULL);
    return;
}
void CGame::mainMenuRedraw()
{
    return;
}
void CGame::resumeRedraw()
{
    return;
}
void CGame::gamingRedraw()
{
    return;
}
void CGame::completeRedraw()
{
    return;
}