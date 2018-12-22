#ifndef __GAME_H__
#define __GAME_H__


#define __DEBUG__

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Timer/CTimer.h"

#ifdef __DEBUG__
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <iostream>


using std::cout;
using std::endl;


#endif

using std::string;


class CGame
{
    private:

    #ifdef __DEBUG__
    string mLogFileName;
    log4cpp::Category& mMainLog;
    #endif



    SDL_Renderer* mRenderer;        // Main Renderer
    SDL_Window* mWindow;            // Main Window

    int mWindowWidth;
    int mWindowHeight;

    bool mQuitGame;                 // Quit Program
    bool mShouldRedraw;             // Should Redraw?

    struct startPageInfo
    {
        SDL_Texture* startPageTexture;
        string startPageFileName;
        long startPageTime;
    }mStartPageInfo;

    struct mainMenuInfo
    {
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

    GAME_STATE mState;
    MAIN_MENU_OPTIONS mMainMenuOption;
    RESUME_MENU_OPTIONS mResumeMenuOption;

    CTimer mMainTimer;

    void handleInput(SDL_Event& event);
    void startPageInput(SDL_Event& event);
    void mainMenuInput(SDL_Event& event);
    void resumeInput(SDL_Event& event);
    void gamingInput(SDL_Event& event);
    void completeInput(SDL_Event& event);

    bool updateData();
    bool startPageUpdateData();
    bool mainMenuUpdateData();
    bool resumeUpdateData();
    bool gamingUpdateData();
    bool completeUpdateData();

    void redraw();
    void startPageRedraw();
    void mainMenuRedraw();
    void resumeRedraw();
    void gamingRedraw();
    void completeRedraw();

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