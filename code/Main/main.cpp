#include "../Game/CGame.h"

int main(int argc,char* argv[])
{
    CGame game(true);
    if(!game.initState())
    {
        return 1;
    }
    game.loadMedia();
    game.mainLoop();
    return 0;
}