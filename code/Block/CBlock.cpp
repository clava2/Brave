#include "CBlock.h"
#include <stdlib.h>

int CBlock::mSmallMap[BLOCK_ALL][4] = {{0xE400,0x4C40,0x4E00,0x8C80},
                                       {0x88C0,0xE800,0xC440,0x2E00},
                                       {0x44C0,0x8E00,0xC880,0xE200},
                                       {0x8888,0xF000,0x8888,0xF000},
                                       {0xCC00,0xCC00,0xCC00,0xCC00},
                                       {0x6C00,0x8C40,0x6C00,0x8C40},
                                       {0xC600,0x4C80,0xC600,0x4C80}};

CBlock::CBlock()
{
    mBlockType = BLOCK_I;
    mBlockState = 0;
}

void CBlock::draw(SDL_Renderer* renderer)
{
    for(int i = 0;i != 4;i++)
    {
        for(int j = 0;j != 4;j++)
        {
            if(mSmallMap[mBlockType][mBlockState] & (0x8000 >> (i*4+j)))
            {
                SDL_Rect area = {mPos.x + mEleWidth * j,mPos.y + mEleHeight * i,mEleWidth,mEleHeight};
                SDL_RenderCopy(renderer,mBlockTexture,NULL,&area);
            }
        }
    }
}

void CBlock::handleInput(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        if(event.key.keysym.sym == SDLK_UP)
        {
            char info[100];
            sprintf(info,"mBlockType = %d,mBlockState = %d,mSmallMap[mBlockType][mState] = %d\n",mBlockType,mBlockState,mSmallMap[mBlockType][mBlockState]);
            mBlockState = (mBlockState + 1)%4;
        }
    }
}

bool CBlock::load(SDL_Renderer* renderer,string blockTexturePath)
{
    SDL_Surface* tempSurface = IMG_Load(blockTexturePath.c_str());
    if(tempSurface == NULL)
    {
        mainLog.warn(string("Error when loading tempSurface!") + SDL_GetError());
        return false;
    }
    mBlockTexture = SDL_CreateTextureFromSurface(renderer,tempSurface);
    mEleWidth = tempSurface->w;
    mEleHeight = tempSurface->h;
    SDL_FreeSurface(tempSurface);
    if(mBlockTexture == NULL)
    {
        mainLog.warn(string("Error when creating texture from surface") + SDL_GetError());
        return false;
    }
    return true;
}

void CBlock::update()
{
}


void CBlock::setPos(SDL_Point pos)
{
    mPos = pos;
}

SDL_Point CBlock::getPos()
{
    return mPos;
}

int CBlock::getMap()
{
    return mSmallMap[mBlockType][mBlockState];
}

SDL_Texture* CBlock::getBlockTexture()
{
    return mBlockTexture;
}