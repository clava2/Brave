#ifndef __TEXT_PANEL__H__
#define __TEXT_PANEL__H__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <yaml-cpp/yaml.h>

using std::string;

class CTextPanel
{
private:
    string      mText;              // 文本面板中显示的文本
    SDL_Rect    mArea;              // 文本显示区域
    YAML::Node  mTextInput;         // 以YAML格式读取配置文件
public:
    
};


#endif