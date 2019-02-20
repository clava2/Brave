#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "../Block/CBlock.h"

using std::vector;


class CBoard
{
    private:

    const int mBoardWidth;
    const int mBoardHeight;
    const int mBlockWidth;
    const int mBlockHeight;

    SDL_Texture* mBackground;

    SDL_Point mMapPos;
    vector<SDL_Texture*> mMap;

    public:

    CBoard();

    void addBlock(CBlock block);

    void setPos(SDL_Point pos);
    int getSmallMap(SDL_Point pos);

    bool load(SDL_Renderer* renderer);
    bool update();
    void draw(SDL_Renderer* renderer);
    
};