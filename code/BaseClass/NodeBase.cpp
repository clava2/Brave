#include "NodeBase.h"
#include <SDL2/SDL_image.h>
#include <yaml-cpp/yaml.h>

CNodeBase::CNodeBase()
{
    mArea.x = 0;
    mArea.y = 0;
    mArea.w = 100;
    mArea.h = 100;
}

CNodeBase::~CNodeBase()
{
    if(mBackground)
    {
        SDL_DestroyTexture(mBackground);
    }
}

void CNodeBase::move(double direction,double speed)
{
}

bool CNodeBase::setBackground(SDL_Renderer* renderer, string path)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(path.c_str());
    if(tempSurface == NULL)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,"Error When Loading background, path = %s", path.c_str());
        return false;
    }
    mBackground = SDL_CreateTextureFromSurface(renderer, tempSurface);
    if(mBackground == NULL)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,"Error When creating Texture, path = %s",path.c_str());
    }
    SDL_FreeSurface(tempSurface);
    return true;
}

bool CNodeBase::loadNode(string configFilePath)
{
    YAML::Node node = YAML::Load(configFilePath);
    mArea.x = node["Nodes"][]
}