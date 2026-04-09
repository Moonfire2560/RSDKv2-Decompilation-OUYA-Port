#ifndef RETROENGINE_H
#define RETROENGINE_H

// Disables POSIX use c++ name blah blah stuff
#pragma warning(disable : 4996)

#ifndef RETRO_USE_ORIGINAL_CODE
#define RETRO_USE_ORIGINAL_CODE (0)
#endif

#ifndef RETRO_USE_MOD_LOADER
#define RETRO_USE_MOD_LOADER (0)
#endif

#if !RETRO_USE_ORIGINAL_CODE
#undef RETRO_USE_MOD_LOADER
#define RETRO_USE_MOD_LOADER (1)
#endif

// ================
// STANDARD LIBS
// ================
#include <stdio.h>
#include <string.h>
#include <cmath>

// ================
// STANDARD TYPES
// ================
typedef unsigned char byte;
typedef signed char sbyte;
typedef unsigned short ushort;
typedef unsigned int uint;

#define RETRO_WIN      (0)
#define RETRO_OSX      (1)
#define RETRO_XBOX_360 (2)
#define RETRO_PS3      (3)
#define RETRO_iOS      (4)
#define RETRO_ANDROID  (5)
#define RETRO_WP7      (6)
#define RETRO_UWP (7)

#define RETRO_STANDARD (0)
#define RETRO_MOBILE   (1)

#if defined _WIN32
#if defined WINAPI_FAMILY
#if WINAPI_FAMILY != WINAPI_FAMILY_APP
#define RETRO_PLATFORM (RETRO_WIN)
#else
#include <WinRTIncludes.hpp>
#define RETRO_PLATFORM (RETRO_UWP)
#endif
#else
#define RETRO_PLATFORM (RETRO_WIN)
#endif
#elif defined __APPLE__
#define RETRO_USING_MOUSE
#define RETRO_USING_TOUCH
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#define RETRO_PLATFORM (RETRO_iOS)
#elif TARGET_OS_IPHONE
#define RETRO_PLATFORM (RETRO_iOS)
#elif TARGET_OS_MAC
#define RETRO_PLATFORM (RETRO_OSX)
#else
#error "Unknown Apple platform"
#endif
#elif defined __ANDROID__
#define RETRO_PLATFORM (RETRO_ANDROID)
#else
#define RETRO_PLATFORM (RETRO_WIN) // Default
#endif

#if RETRO_PLATFORM == RETRO_UWP
#define BASE_PATH            ""
#define DEFAULT_SCREEN_XSIZE 320
#define DEFAULT_FULLSCREEN   false
#elif RETRO_PLATFORM == RETRO_ANDROID
#define BASE_PATH "/sdcard/RSDK/v2/"
#define RETRO_USING_MOUSE
#define RETRO_USING_TOUCH
#define DEFAULT_SCREEN_XSIZE 320
#define DEFAULT_FULLSCREEN   false
#else
#define BASE_PATH ""
#define RETRO_USING_MOUSE
#define RETRO_USING_TOUCH
#define DEFAULT_SCREEN_XSIZE 320
#define DEFAULT_FULLSCREEN   false
#endif

#if RETRO_PLATFORM == RETRO_WIN || RETRO_PLATFORM == RETRO_OSX || RETRO_PLATFORM == RETRO_iOS || RETRO_PLATFORM == RETRO_UWP || RETRO_PLATFORM == RETRO_ANDROID
#define RETRO_USING_SDL1 (0)
#define RETRO_USING_SDL2 (1)
#else
#define RETRO_USING_SDL1 (0)
#define RETRO_USING_SDL2 (0)
#endif

enum RetroStates {
    ENGINE_SYSMENU     = 0,
    ENGINE_MAINGAME    = 1,
    ENGINE_INITSYSMENU = 2,
    ENGINE_EXITGAME    = 3,
};

#define SCREEN_YSIZE   (240)
#define SCREEN_CENTERY (SCREEN_YSIZE / 2)

#if RETRO_PLATFORM == RETRO_WIN || RETRO_PLATFORM == RETRO_UWP
#if RETRO_USING_SDL2
#include <SDL.h>
#elif RETRO_USING_SDL1
#include <SDL.h>
#endif
#include <vorbis/vorbisfile.h>
#elif RETRO_PLATFORM == RETRO_OSX
#include <SDL2/SDL.h>
#include <Vorbis/vorbisfile.h>
#include "cocoaHelpers.hpp"
#elif RETRO_PLATFORM == RETRO_iOS
#include <SDL2/SDL.h>
#include <vorbis/vorbisfile.h>
#include "cocoaHelpers.hpp"
#elif RETRO_PLATFORM == RETRO_ANDROID
#include <SDL.h>
#include <vorbis/vorbisfile.h>
#endif

extern bool usingCWD;
extern bool engineDebugMode;

#include "Ini.hpp"
#include "Math.hpp"
#include "String.hpp"
#include "Reader.hpp"
#include "Animation.hpp"
#include "Audio.hpp"
#include "Input.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Palette.hpp"
#include "Drawing.hpp"
#include "Collision.hpp"
#include "Scene.hpp"
#include "Script.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Video.hpp"
#include "Userdata.hpp"
#include "Debug.hpp"
#include "ModAPI.hpp"

class RetroEngine {
public:
    RetroEngine() {}

    bool UseBinFile         = false;
    bool usingDataFileStore = false;
    bool forceFolder        = false;

    char dataFile[0x80];

    bool initialised = false;
    bool GameRunning     = false;

    int GameMode    = ENGINE_MAINGAME;
    byte ColourMode = 1;

    int frameSkipSetting = 0;
    int frameSkipTimer   = 0;

    int startList_Game  = -1;
    int startStage_Game = -1;

    bool consoleEnabled  = false;
    bool devMenu         = false;
    int startList        = -1;
    int startStage       = -1;
    int gameSpeed        = 1;
    int fastForwardSpeed = 8;
    bool masterPaused    = false;
    bool frameStep       = false;

    char startSceneFolder[0x10];
    char startSceneID[0x10];

    void Init();
    void Run();

    bool LoadGameConfig(const char *Filepath);

    char GameWindowText[0x40];
    char GameDescriptionText[0x100];

    byte *FrameBuffer = nullptr;

    bool isFullScreen = false;

    bool startFullScreen  = false;
    bool borderless       = false;
    bool vsync            = false;
    bool enhancedScaling  = true;
    int windowScale       = 2;
    int refreshRate       = 60;
    int screenRefreshRate = 60;
    int targetRefreshRate = 60;

    uint frameCount      = 0;
    int renderFrameIndex = 0;
    int skipFrameIndex   = 0;

    int windowXSize;
    int windowYSize;

#if RETRO_USING_SDL2
    SDL_Window *window          = nullptr;
    SDL_Renderer *renderer      = nullptr;
    SDL_Texture *screenBuffer   = nullptr;
    SDL_Texture *screenBuffer2x = nullptr;
    SDL_Texture *videoBuffer    = nullptr;

    SDL_Event sdlEvents;
#endif

#if RETRO_USING_SDL1
    SDL_Surface *windowSurface = nullptr;

    SDL_Surface *screenBuffer   = nullptr;
    SDL_Surface *screenBuffer2x = nullptr;
    SDL_Surface *videoBuffer    = nullptr;

    SDL_Event sdlEvents;
#endif
};

extern RetroEngine Engine;
#endif // !RETROENGINE_H
