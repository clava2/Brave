#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../Timer/CTimer.h"
#include "../Board/CBoard.h"
#include "../GUI/CButton.h"
#include "../CrossFile/CrossFile.h"
#include "../Block/CBlock.h"


using std::cout;
using std::endl;
using std::string;


enum GAME_STATE
{
    GAME_STATE_START_PAGE,
    GAME_STATE_MAIN_MENU,
    GAME_STATE_GAMING,
    GAME_STATE_RESUME_MENU,
    GAME_STATE_COMPLETE,
    GAME_STATE_ALL
};

enum MAIN_MENU_OPTIONS
{
    MAIN_MENU_OPTION_START,
    MAIN_MENU_OPTION_RESUME,
    MAIN_MENU_OPTION_SETTING,
    MAIN_MENU_OPTION_QUIT,
    MAIN_MENU_OPTION_ALL
};

enum RESUME_MENU_OPTIONS
{
    RESUME_MENU_OPTION_RESUME,
    RESUME_MENU_OPTION_SETTING,
    RESUME_MENU_OPTION_RETURN,
    RESUME_MENU_OPTION_QUIT
};



class CGame
{
    private:


    // Window and Renderer
    SDL_Renderer* mRenderer;        // Main Renderer
    SDL_Window* mWindow;            // Main Window
    int mWindowWidth;
    int mWindowHeight;

    struct startPageInfo
    {
        SDL_Texture* startPageTexture;
        string startPageFileName;
        long startPageTime;
    }mStartPageInfo;

    struct mainMenuInfo
    {
        CButton startButton;
        CButton settingButton;
        CButton quitButton;
    }mMainMenuInfo;

    struct gamingInfo
    {
    }mGamingInfo;

    struct resumeMenuInfo
    {
    }mResumeMenuInfo;

    struct completeInfo
    {
    }mCompleteInfo;


    // Flow Control
    GAME_STATE mState;
    MAIN_MENU_OPTIONS mMainMenuOption;
    RESUME_MENU_OPTIONS mResumeMenuOption;

    bool mQuitGame;                 // Quit Program
    bool mShouldRedraw;             // Should Redraw?

    // Main Timer
    CTimer mMainTimer;

    // Input Handle
    void handleInput(SDL_Event& event);
    void startPageInput(SDL_Event& event);
    void mainMenuInput(SDL_Event& event);
    void resumeInput(SDL_Event& event);
    void gamingInput(SDL_Event& event);
    void completeInput(SDL_Event& event);

    // Data Update
    bool updateData();
    bool startPageUpdateData();
    bool mainMenuUpdateData();
    bool resumeUpdateData();
    bool gamingUpdateData();
    bool completeUpdateData();

    // Render
    void redraw();
    void startPageRedraw();
    void mainMenuRedraw();
    void resumeRedraw();
    void gamingRedraw();
    void completeRedraw();

    // Other Game Variable
    CBoard mBoard;

    CBlock mMainBlock;

    public:

    /**
     * @brief Construct a new CGame object
     * 
     * @param initSDL 
     *        false     :DO NOT initialize SDL
     *        true      :initialize SDL
     */
    CGame(bool initSDL = false);

    /**
     * @brief initialize starting state of the program
     * 
     * return true      : initialize sucessful
     * return false     : initialize failed
     */
    bool initState();

    /**
     * @brief Load media used in the game
     * 
     * @return bool
     *         true     : success
     *         false    : failure while loading
     * 
     */
    bool loadMedia();

    /**
     * @brief main game loop
     * 
     */
    void mainLoop();
};


#endif