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
}

void CNodeBase::move(double direction,double speed)
{
}

bool CNodeBase::loadNode(string nodeID, YAML::Node subNodes)
{
    mNodeName = nodeID;
}

bool CNodeBase::loadMedia(SDL_Renderer* renderer)
{
    return false;
}