#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "CGame.h"
#include "../SceneTree/SceneTree.h"

using std::cout;
using std::endl;

CGame::CGame()
{
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
    mCommonConfigInput  = YAML::LoadFile("common config.yaml");

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
    mSceneConfigInput = YAML::LoadFile("scene config.yaml");

    CSceneTreeNode* newNode = new CSceneTreeNode();
    CSceneBase*     tempScene = new CSceneBase();
    for(YAML::const_iterator ite = mSceneConfigInput.begin();ite != mSceneConfigInput.end();++ite)
    {
        newNode->mSceneName = ite->first.as<string>();
        newNode->mParent    = mSceneTree->searchTreeNode((ite->second)["parent"].as<string>);
        tempScene->constructScene((*ite).second["scene content"].as<string>());
    }
}

bool CGame::loadMedia()
{
}