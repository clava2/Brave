#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "../BaseClass/NodeBase.h"


#include "../CrossFile/CrossFile.h"



using std::string;

enum BUTTON_STATE
{
    BUTTON_STATE_NORMAL,
    BUTTON_STATE_IN,
    BUTTON_STATE_DOWN,
    BUTTON_STATE_DISABLED,
    BUTTON_STATE_ALL
};

enum BUTTON_CALLBACK
{
    BUTTON_CALLBACK_IN,
    BUTTON_CALLBACK_DOWN,
    BUTTON_CALLBACK_UP,
    BUTTON_CALLBACK_LEAVE,
    BUTTON_CALLBACK_ALL
};

class CButton : CNodeBase
{
    private:


    SDL_Texture* mTexture[BUTTON_STATE_ALL];

    SDL_Texture* mText[BUTTON_STATE_ALL];

    SDL_Rect mTextArea;
    bool mIsEnabled;
    BUTTON_STATE mState;

    bool isMouseInButton(SDL_Point pos);

    void* (*mCallbacks[BUTTON_CALLBACK_ALL])(void* param);

    void* mCallbackParams[BUTTON_CALLBACK_ALL];

    BUTTON_STATE mLastState;

    public:

    CButton(SDL_Renderer* renderer = NULL);
    
    //void setDisable(bool disable);
    bool setTexture(SDL_Renderer* renderer,BUTTON_STATE state,string path);
    bool setTextures(SDL_Renderer* renderer,string* path);
    void setPos(SDL_Point pos);
    void setText(SDL_Renderer* renderer,string* text);
    void setText(SDL_Renderer* renderer,string text);
    void setCallback(BUTTON_CALLBACK callbackType,void* (*callback)(void* param),void* param);
    void handleEvent(SDL_Event event);
    void update();
    void render(SDL_Renderer* renderer);


    SDL_Rect getArea();
};