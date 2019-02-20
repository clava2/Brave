#include "CGame.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



void* quit(void* param)
{
    *(bool*)(param) = true;
    return NULL;
}

void* startGame(void* param)
{
    *(GAME_STATE*)param = GAME_STATE_GAMING;
    return NULL;
}




CGame::CGame(bool init)
{
    log4cpp::PropertyConfigurator::configure("../log4cpp.properities");
    int errorCode = SDL_Init(SDL_INIT_EVERYTHING);
    if(errorCode)
    {
        mainLog.error("Can not initialize SDL!");
        return;
    }
    errorCode = IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF);
    if(errorCode)
    {
        mainLog.error("Can not initialize SDL_Image");
    }
    errorCode = TTF_Init();
    if(errorCode)
    {
        mainLog.error("Can not initializ SDL_TTF");
    }
}

bool CGame::initState()
{
    mWindow = SDL_CreateWindow("Gaming",0,0,100,100,SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(mWindow == NULL)
    {
        mainLog.error("Can not create window");
        return false;
    }
    SDL_GetWindowSize(mWindow,&mWindowWidth,&mWindowHeight);
    mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED);
    if(mRenderer == NULL)
    {
        mainLog.error("Can not create renderer");
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
        mainLog.warn("Can not load start_page.png");
        return false;
    }
    mStartPageInfo.startPageTexture = SDL_CreateTextureFromSurface(mRenderer,tempSurface);
    if(mStartPageInfo.startPageTexture == NULL)
    {
        mainLog.warn(string("can not create start page texture from surface")+SDL_GetError());
        return false;
    }
    SDL_FreeSurface(tempSurface);
    tempSurface = NULL;


    bool loadResult = false;

    loadResult = mBoard.load(mRenderer);
    if (!loadResult)
    {
        mainLog.warn("loading Board Error!" + string(SDL_GetError()));
        return false;
    }

    string paths[4] = {"../resources/button/default_normal.png",
                        "../resources/button/default_in.png",
                        "../resources/button/default_down.png",
                        "../resources/button/default_disabled.png"};
    string text = "郑聪";

    mMainMenuInfo.startButton.setTextures(mRenderer,paths);
    mMainMenuInfo.settingButton.setTextures(mRenderer,paths);
    mMainMenuInfo.quitButton.setTextures(mRenderer,paths);

    mMainMenuInfo.startButton.setText(mRenderer,"开始");
    mMainMenuInfo.settingButton.setText(mRenderer,"设置");
    mMainMenuInfo.quitButton.setText(mRenderer,"退出");

    SDL_Rect area = mMainMenuInfo.startButton.getArea();
    int x1 = mWindowWidth/2 - area.w/2;
    int y1 = mWindowHeight/4 - area.h/2;
    mMainMenuInfo.startButton.setPos({x1,y1});
    y1 = y1 + mWindowHeight/4;
    mMainMenuInfo.settingButton.setPos({x1,y1});
    y1 = y1 + mWindowHeight/4;
    mMainMenuInfo.quitButton.setPos({x1,y1});

    mMainMenuInfo.quitButton.setCallback(BUTTON_CALLBACK_DOWN,quit,&mQuitGame);
    mMainMenuInfo.startButton.setCallback(BUTTON_CALLBACK_UP,startGame,&mState);

    mMainBlock.load(mRenderer,"../resources/block/green.png");
    mMainBlock.setPos({0,0});

    CBlock block1;
    block1.load(mRenderer,"../resources/block/green.png");
    block1.setPos({0,0});

    mBoard.addBlock(block1);
    block1.setPos({1,1});
    mBoard.addBlock(block1);
    block1.setPos({2,2});
    mBoard.addBlock(block1);
    mBoard.setPos({0,mWindowHeight});

    return true;
}

void CGame::mainLoop()
{
    SDL_Event event;

    SDL_SetRenderDrawColor(mRenderer,0x00,0x00,0x00,0x00);
    
    while(!mQuitGame)
    {
        if(SDL_PollEvent(&event))
        {
            handleInput(event);
        }
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
    mMainMenuInfo.startButton.handleEvent(event);
    mMainMenuInfo.settingButton.handleEvent(event);
    mMainMenuInfo.quitButton.handleEvent(event);
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
    mMainBlock.handleInput(event);
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
    mMainMenuInfo.startButton.update();
    mMainMenuInfo.settingButton.update();
    mMainMenuInfo.quitButton.update();
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
    mMainMenuInfo.startButton.draw(mRenderer);
    mMainMenuInfo.settingButton.draw(mRenderer);
    mMainMenuInfo.quitButton.draw(mRenderer);
    return;
}
void CGame::resumeRedraw()
{
    return;
}
void CGame::gamingRedraw()
{
    mBoard.draw(mRenderer);
    mMainBlock.draw(mRenderer);
    return;
}
void CGame::completeRedraw()
{
    return;
}