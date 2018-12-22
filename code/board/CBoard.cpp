#include "CBoard.h"

CBoard::CBoard():
mBoardWidth(10),mBoardHeight(20),mBlockWidth(48),mBlockHeight(48)
{
    mMainBoard = new int[(mBoardWidth+1)*(mBoardHeight+1)];
}

void CBoard::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer,)
}