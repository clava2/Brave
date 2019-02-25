#ifndef __NODE_BASE_H__
#define __NODE_BASE_H__

#include <SDL2/SDL.h>
#include <string>
#include <yaml-cpp/yaml.h>

using std::string;

class CNodeBase
{
    protected:
    SDL_Rect mArea;             // 节点位置
    string   mNodeName;         // 节点名称
    bool     mActive;           //是否激活
    public:
    CNodeBase();
    ~CNodeBase();

    public:
    virtual void move(double direction,double speed);
    virtual bool loadNode(string nodeID,YAML::Node subNodes);
    virtual bool loadMedia(SDL_Renderer* renderer);
    // bool onKeyboardDown(int key);
    // bool onMouseKeyDown(int key);
};

#endif