#ifndef __NODE_BASE_H__
#define __NODE_BASE_H__

#include <SDL2/SDL.h>
#include <string>

using std::string;

class CNodeBase
{
    protected:
    SDL_Rect mArea;             // 节点位置
    string   mNodeName;         // 节点名称
    SDL_Texture* mBackground;   // 背景纹理
    public:
    CNodeBase();
    ~CNodeBase();

    protected:
    void move(double direction,double speed);
    bool setBackground(SDL_Renderer* renderer, string filePath);
    bool loadNode(string configFilePath);
    // bool onKeyboardDown(int key);
    // bool onMouseKeyDown(int key);
};

#endif