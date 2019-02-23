#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <yaml-cpp/yaml.h>
#include "../SceneTree/SceneTree.h"

class CGame
{
    private:

    int             mWindowWidth;
    int             mWindowHeight;
    SDL_Point       mWindowPosition;

    SDL_Window*     mMainWindow;
    SDL_Renderer*   mRenderer;
    CSceneTree*     mSceneTree;

    YAML::Node      mCommonConfigInput;
    YAML::Emitter   mCommonConfigOutput;

    YAML::Node      mSceneConfigInput;
    YAML::Emitter   mSceneConfigOutput;

    public:
    CGame();
    ~CGame();

    bool init(string title = "Untitled Window",int x = 0,int y = 0,int w = 100,int h = 100);
    bool loadScene();
    bool loadMedia();
    void mainLoop();

    private:
    void render();
    void update();
};


#endif