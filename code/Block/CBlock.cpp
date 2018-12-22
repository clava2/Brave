#include "CBlock.h"
#include <stdlib.h>

CBlock::CBlock()
{
    mBlockType = (BLOCK_TYPE)(rand()%BLOCK_ALL);
}

void CBlock::draw(SDL_Renderer* renderer)
{
    
}

void CBlock::handleInput(SDL_Event event)
{
}

void CBlock::update()
{
}