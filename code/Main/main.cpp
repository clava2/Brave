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
    game.loadScene();
    return 0;
}