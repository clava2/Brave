#include "CBoard.h"
#include <SDL2/SDL_image.h>

CBoard::CBoard():
mBoardWidth(10),mBoardHeight(20),mBlockWidth(16),mBlockHeight(16)
{
    for(int i = 0;i != mBoardWidth+6;i++)
    {
        for(int j= 0;j != mBoardHeight+3;j++)
        {
            mMap.push_back(NULL);
        }
    }
    mMapPos = {500,500};
}

bool CBoard::load(SDL_Renderer* renderer)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load("../resources/pictures/background.png");
    if(tempSurface == NULL)
    {
        return false;
    }
    mBackground = SDL_CreateTextureFromSurface(renderer,tempSurface);
    if(mBackground == NULL)
    {
        SDL_FreeSurface(tempSurface);
        return false;
    }
    SDL_FreeSurface(tempSurface);
    return true;
}

bool CBoard::update()
{
    
}

void CBoard::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer,mBackground,NULL,NULL);
    for(int i = 0;i != mBoardWidth;i++)
    {
        for(int j = 0;j != mBoardHeight;j++)
        {
            SDL_Rect area = {mMapPos.x + mBlockWidth*i,mMapPos.y - mBlockHeight*(j + 1),mBlockWidth,mBlockHeight};
            SDL_RenderCopy(renderer,mMap[i*mBoardWidth + j],NULL,&area);
        }
    }
}

void CBoard::addBlock(CBlock block)
{
    int map = block.getMap();
    SDL_Texture* tempTexture = block.getBlockTexture();
    SDL_Point pos = block.getPos();

    for(int i = 0;i != 4;i++)
    {
        for(int j = 0;j != 4;j++)
        {
            if(map & (0x80 >> (i*4+j)))
            {
                mMap[pos.y * mBoardWidth + pos.x] = tempTexture;
            }
        }
    }
}

void CBoard::setPos(SDL_Point pos)
{
    mMapPos = pos;
}

int CBoard::getSmallMap(SDL_Point pos)
{
    int result = 0;
    for(int i = 0;i!= 4;i++)
    {
        for(int j = 0;j != 4;j++)
        {
            if((mMap[i*mBoardWidth + j]) || (pos.x + i > mBoardWidth) || (pos.y + j > mBoardHeight))
            {
                result += 1;
            }
            result = result << 1;
        }
    }
    return result;
}