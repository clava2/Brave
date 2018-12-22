#include <SDL2/SDL.h>


class CBoard
{
    private:

    const int mBoardWidth;
    const int mBoardHeight;
    const int mBlockWidth;
    const int mBlockHheight;
    int* mMainBoard;

    public:

    CBoard();
    bool update();
    void draw(SDL_Renderer* renderer);
    
};