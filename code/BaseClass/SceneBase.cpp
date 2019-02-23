#include "SceneBase.h"
#include <yaml-cpp/yaml.h>

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
    YAML::Node sceneNode = YAML::Load(configFilePath);
    mArea.x = sceneNode["x"].as<int>();
    mArea.y = sceneNode["y"].as<int>();
    mArea.w = sceneNode["width"].as<int>();
    mArea.h = sceneNode["height"].as<int>();

    mActive = sceneNode["active"].as<bool>();

    CNodeBase* tempNode = new CNodeBase();
    for(YAML::const_iterator ite = sceneNode["nodes"].begin();ite != sceneNode["node"].end();++ite)
    {
        
    }
}

