#include <yaml-cpp/yaml.h>
#include <fstream>
#include "../SceneTree/SceneTree.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>
#include <string>
#include "../Game/CGame.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

int main(int argc,char* argv[])
{
    CGame game;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Initializing Game...");
    game.init();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Loading Scenes...");
    game.loadScene();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Loading Media...");
    game.loadMedia();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,"Entering Main loop...");
    game.mainLoop();
    return 0;
}