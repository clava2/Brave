#ifndef __BLOCK__
#define __BLOCK__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "../CrossFile/CrossFile.h"

using std::string;


    enum BLOCK_TYPE
    {
        BLOCK_T,
        BLOCK_L,
        BLOCK_J,
        BLOCK_I,
        BLOCK_O,
        BLOCK_S,
        BLOCK_Z,
        BLOCK_ALL
    };

class CBlock
{
    private:

    BLOCK_TYPE mBlockType;

    SDL_Texture* mBlockTexture;

    static int mSmallMap[BLOCK_ALL][4];

    int mBlockState;

    SDL_Point mPos;
    int mEleWidth;
    int mEleHeight;

    public:
    CBlock();

    int getMap();
    SDL_Texture* getBlockTexture();
    void setPos(SDL_Point pos);

    SDL_Point getPos();

    void handleInput(SDL_Event& event);
    bool load(SDL_Renderer* renderer,string blockTexturePath);
    void draw(SDL_Renderer* renderer);
    void update();
};


#endif