#ifndef __SCENE_BASE_H__
#define __SCENE_BASE_H__

#include <SDL2/SDL.h>
#include <vector>
#include "NodeBase.h"

using std::vector;

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
};

#endif