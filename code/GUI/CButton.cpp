#include "CButton.h"

CButton::CButton(SDL_Renderer* renderer)
{
    mArea.x = 0;
    mArea.y = 0;
    mState = BUTTON_STATE_NORMAL;
    mLastState = BUTTON_STATE_NORMAL;
    for(int i = 0;i != BUTTON_CALLBACK_ALL;i++)
    {
        mCallbacks[i] = NULL;
        mCallbackParams[i] = NULL;
    }
    if(renderer == NULL)
    {
        mainLog.info("renderer in CButton Construction is NULL, Returnning");
        return;
    }
    string paths[4] = {"../resources/button/default_normal.png",
                        "../resources/button/default_in.png",
                        "../resources/button/default_down.png",
                        "../resources/button/default_disabled.png"};
    setTextures(renderer,paths);
}

bool CButton::setTexture(SDL_Renderer* renderer,BUTTON_STATE state,string path)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(path.c_str());
    mArea.w = tempSurface->w;
    mArea.h = tempSurface->h;
    if(tempSurface == NULL)
    {
        mainLog.info("Error When Loading From Image FIle" + path);
        return false;
    }
    mTexture[state] = SDL_CreateTextureFromSurface(renderer,tempSurface);
    SDL_FreeSurface(tempSurface);
    if(mTexture[state] == NULL)
    {
        mainLog.info("Error When Creating Texture From Surface" + path);
        return false;
    }
    mainLog.info("Loading "+ path + " Successfully!");
    return true;
}

bool CButton::setTextures(SDL_Renderer* renderer,string* path)
{
    SDL_Surface* tempSurface = NULL;
    for(int i = 0;i != BUTTON_STATE_ALL;i++)
    {
        tempSurface = IMG_Load(path[i].c_str());
        mArea.h = tempSurface->h;
        mArea.w = tempSurface->w;
        if(tempSurface == NULL)
        {
            mainLog.info("Loading Surface From File "+path[i] + " Failed!");
            return false;
        }
        mTexture[i] = SDL_CreateTextureFromSurface(renderer,tempSurface);
        SDL_FreeSurface(tempSurface);
        if(mTexture[i] == NULL)
        {
            mainLog.info("Creating Texture From File " + path[i] + "Failed!");
            return false;
        }
    }
    mainLog.info("Setting Texture Successfully!");
    return true;
}

bool CButton::isMouseInButton(SDL_Point pos)
{
    if((pos.x < mArea.x + mArea.w) && (pos.x > mArea.x) && (pos.y < mArea.y + mArea.h) && (pos.y > mArea.y))
    {
        return true;
    }
    return false;
}

void CButton::handleEvent(SDL_Event event)
{
    if(event.type == SDL_MOUSEMOTION)
    {
        SDL_Point pos = {event.motion.x,event.motion.y};
        if(isMouseInButton(pos)&&mState != BUTTON_STATE_DOWN)
        {
            mState = BUTTON_STATE_IN;
        }
        else
        {
            mState = BUTTON_STATE_NORMAL;
        }
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point pos = {event.button.x,event.button.y};
        if(isMouseInButton(pos))
        {
            mState = BUTTON_STATE_DOWN;
        }
    }
    if(event.type == SDL_MOUSEBUTTONUP)
    {
        SDL_Point pos = {event.button.x,event.button.y};
        if(isMouseInButton(pos))
        {
            mState = BUTTON_STATE_IN;
        }
    }
}

void CButton::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer,mTexture[mState],NULL,&mArea);
    SDL_RenderCopy(renderer,mText[mState],NULL,&mTextArea);
}

void CButton::setPos(SDL_Point pos)
{
    mArea.x = pos.x;
    mArea.y = pos.y;
    mTextArea.x = mArea.x + mArea.w/2 - mTextArea.w/2;
    mTextArea.y = mArea.y + mArea.h/2 - mTextArea.h/2;
}

void CButton::update()
{
    if((mLastState == BUTTON_STATE_NORMAL) && (mState == BUTTON_STATE_IN) && 
        mCallbacks[BUTTON_CALLBACK_IN] && (mCallbackParams[BUTTON_CALLBACK_IN]))
    {
        mCallbacks[BUTTON_CALLBACK_IN](mCallbackParams[BUTTON_CALLBACK_IN]);
    }
    else if((mLastState == BUTTON_STATE_IN) && (mState == BUTTON_STATE_DOWN) && 
        mCallbacks[BUTTON_CALLBACK_DOWN] && (mCallbackParams[BUTTON_CALLBACK_DOWN]))
    {
        mCallbacks[BUTTON_CALLBACK_DOWN](mCallbackParams[BUTTON_CALLBACK_DOWN]);
    }
    else if((mLastState == BUTTON_STATE_DOWN) && (mState == BUTTON_STATE_IN) && 
        mCallbacks[BUTTON_CALLBACK_UP] && (mCallbackParams[BUTTON_CALLBACK_UP]))
    {
        mCallbacks[BUTTON_CALLBACK_UP](mCallbackParams[BUTTON_CALLBACK_UP]);
    }
    else if((mLastState == BUTTON_STATE_IN) && (mState == BUTTON_STATE_NORMAL) &&
        mCallbacks[BUTTON_CALLBACK_LEAVE] && (mCallbackParams[BUTTON_CALLBACK_LEAVE]))
    {
        mCallbacks[BUTTON_CALLBACK_LEAVE](mCallbackParams[BUTTON_CALLBACK_LEAVE]);
    }
    mLastState = mState;
}

void CButton::setText(SDL_Renderer* renderer,string* text)
{
    TTF_Font* font = TTF_OpenFont("../resources/font/button_font.otf",36);
    if (font == NULL)
    {
        mainLog.error(string("Error When Opening Font!") + SDL_GetError());
        return;
    }
    SDL_Color fg = {0x00,0x00,0x00,0xff};
    SDL_Surface* tempSurface = NULL;
    for(int i = 0;i != 4;i++)
    {
        tempSurface = TTF_RenderUTF8_Blended(font,text[i].c_str(),fg);
        mTextArea.w = tempSurface->w;
        mTextArea.h = tempSurface->h;
        mText[i] = SDL_CreateTextureFromSurface(renderer,tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    mTextArea.x = mArea.x+mArea.w/2-mTextArea.w/2;
    mTextArea.y = mArea.y + mArea.h/2 - mTextArea.h/2;
}


void CButton::setText(SDL_Renderer* renderer,string text)
{
    TTF_Font* font = TTF_OpenFont("../resources/font/button_font.otf",36);
    if (font == NULL)
    {
        mainLog.error(string("Error When Opening Font!") + SDL_GetError());
        return;
    }
    SDL_Color fg = {0x00,0x00,0x00,0xff};
    SDL_Surface* tempSurface = NULL;
    for(int i = 0;i != 4;i++)
    {
        tempSurface = TTF_RenderUTF8_Blended(font,text.c_str(),fg);
        mTextArea.w = tempSurface->w;
        mTextArea.h = tempSurface->h;
        mText[i] = SDL_CreateTextureFromSurface(renderer,tempSurface);
        SDL_FreeSurface(tempSurface);
    }
    mTextArea.x = mArea.x+mArea.w/2-mTextArea.w/2;
    mTextArea.y = mArea.y + mArea.h/2 - mTextArea.h/2;
}

void CButton::setCallback(BUTTON_CALLBACK callbackType,void* (*callback)(void* param),void* param)
{
    mCallbacks[callbackType] = callback;
    mCallbackParams[callbackType] = param;
}

SDL_Rect CButton::getArea()
{
    return mArea;
}