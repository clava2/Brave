#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include <SDL2/SDL.h>
#include <vector>
#include "NodeBase.h"
#include "../CrossFile/CrossFile.h"

using std::vector;


enum SCENE_MESSAGE
{
    SCENE_MESSAGE_QUIT_GAME,
    SCENE_MESSAGE_QUIT_SCENE,
    SCENE_MESSAGE_ENTER_SUBSCENE,
    SCENE_MESSAGE_ALL
};

class CSceneBase
{
    protected:
    SDL_Rect mArea;
    bool mActive;
    vector<CNodeBase*> mNodeList;
    public:
    CSceneBase();
    ~CSceneBase();
    bool loadMedia(SDL_Renderer* renderer);
    bool render();
    bool constructScene(string configFilePath);
    SCENE_MESSAGE handleInput(SDL_Event event);
};

#endif