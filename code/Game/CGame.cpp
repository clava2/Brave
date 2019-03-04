#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "CGame.h"
#include "../SceneTree/SceneTree.h"

using std::cout;
using std::endl;

CGame::CGame()
{
    mSceneTree = new CSceneTree();
    if(SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL Was not initialized, SDL_GetError() = %s",SDL_GetError());
        return;
    }
    mMainWindow = SDL_CreateWindow("Untitled Window",0,0,100,100,SDL_WINDOW_SHOWN);
    if(mMainWindow == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "Create Window Failed, SDL_GetError() = %s",SDL_GetError());
        return;
    }
    mRenderer = SDL_CreateRenderer(mMainWindow,-1,SDL_RENDERER_ACCELERATED);
    if(mRenderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ASSERT, "Create Renderer Failed, SDL_GetError() = %s", SDL_GetError());
        return;
    }
}

CGame::~CGame()
{

}

bool CGame::init(string title,int x,int y,int w,int h)
{
    mCommonConfigInput  = YAML::LoadFile("../resources/configures/common config.yaml");

    if(mMainWindow)
    {
        SDL_DestroyWindow(mMainWindow);
        mMainWindow = NULL;
    }
    if(mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = NULL;
    }
    mMainWindow = SDL_CreateWindow(title.c_str(),x,y,w,h,SDL_WINDOW_SHOWN);
    if(mMainWindow == NULL)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_ASSERT, "Creating Main Window Error, SDL_GetError() = %s",SDL_GetError());
        return false;
    }
    mRenderer = SDL_CreateRenderer(mMainWindow,-1,SDL_RENDERER_ACCELERATED);
    if(mRenderer == NULL)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_ASSERT, "Creating Renderer Error, SDL_GetError() = %s",SDL_GetError());
        return false;
    }
    return true;
}

bool CGame::loadScene()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"scene tree path: %s",
                        mCommonConfigInput["scene tree path"].as<string>().c_str());
    mSceneConfigInput = YAML::LoadFile(configurePathPrefix + mCommonConfigInput["scene tree path"].as<string>());

    mSceneTree->setRootScene(mSceneConfigInput["root"]["scene content path"].as<string>());
    for(YAML::const_iterator ite = mSceneConfigInput.begin();ite != mSceneConfigInput.end();++ite)
    {
        if(ite->first.as<string>() == "root")
        {
            continue;
        }
        CSceneTreeNode* newNode = new CSceneTreeNode();
        CSceneBase*     tempScene = new CSceneBase();
        newNode->mSceneName = ite->first.as<string>();
        newNode->mParent    = mSceneTree->searchTreeNode((ite->second)["parent"].as<string>());
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"searched scene node: %s, constructing scene throught file: %s ",
                        (ite->second)["parent"].as<string>().c_str(),(ite->second)["scene content path"].as<string>().c_str());
        tempScene->constructScene((*ite).second["scene content path"].as<string>());
        newNode->mScene = tempScene;
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Complete constructing scene: %s",newNode->mSceneName.c_str());
        newNode->mParent->mChildNode.push_back(newNode);
        mSceneTree->addChild((ite->second)["parent"].as<string>(),newNode);
    }
    return true;
}

bool CGame::loadMedia()
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Entered in CGame::loadMedia()");
    mSceneTree->loadMedia(mRenderer);
    return true;
}

void CGame::mainLoop()
{
    while(!mQuit)
    {
        processInput();
        if(mMainTimer.getCurrentTick() > 1./mUpdateRate)
        {
            mMainTimer.start();
            update();
        }
        render();
    }
}

void CGame::update()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    mSceneTree->getCurrentScene()->handleInput(&event);
}