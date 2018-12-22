#ifndef __BLOCK__
#define __BLOCK__

#include <SDL2/SDL.h>


class CBlock
{
    private:

    enum BLOCK_TYPE
    {
        BLOCK_T,
        BLOCK_L,
        BLOCK_LEFT_L,
        BLOCK_I,
        BLOCK_O,
        BLOCK_LEFT_Z,
        BLOCK_RIGHT_Z,
        BLOCK_ALL
    };

    BLOCK_TYPE mBlockType;

    int mBlockState;

    public:
    CBlock();

    void handleInput(SDL_Event event);
    void draw(SDL_Renderer* renderer);
    void update();
};


#endif