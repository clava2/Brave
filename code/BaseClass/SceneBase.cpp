#include "SceneBase.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

using std::cout;
using std::endl;

CSceneBase::CSceneBase()
{
}


CSceneBase::~CSceneBase()
{
}


bool CSceneBase::render()
{
}


bool CSceneBase::constructScene(string configFilePath)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Starting constructing scene from %s",configFilePath.c_str());
    YAML::Node sceneNode = YAML::LoadFile(configurePathPrefix + configFilePath);
    mArea.x = sceneNode["x"].as<int>();
    mArea.y = sceneNode["y"].as<int>();
    mArea.w = sceneNode["width"].as<int>();
    mArea.h = sceneNode["height"].as<int>();

    mActive = sceneNode["active"].as<bool>();

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Loading nodes");

    for(YAML::const_iterator ite = sceneNode["nodes"].begin();ite != sceneNode["nodes"].end();++ite)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Node type = %s",ite->second["type"].as<string>().c_str());
        CNodeBase* tempNode = getNodePointer(ite->second["type"].as<string>());
        tempNode->loadNode(ite->first.as<string>(),ite->second);
        mNodeList.push_back(tempNode);
        cout << "pushed tempNode!" << endl;
    }
}

bool CSceneBase::loadMedia(SDL_Renderer* renderer)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Entered CSceneBase::loadMedia()");
    cout << mNodeList.size() << endl;
    for(CNodeBase* tempNode : mNodeList)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Loading Media of Node ");
        tempNode->loadMedia(renderer);
    }
}

SCENE_MESSAGE CSceneBase::handleInput(SDL_Event event)
{
    switch(event.type)
    {
        case SDL_KEYUP:
        if(event.key.keysym.sym == SDLK_ESCAPE)
        {
            return SCENE_MESSAGE_QUIT_SCENE;
        }
    }
}