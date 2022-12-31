#include "Game.h"

#include <cstdlib>
#include <ctime>

#include "Constants.h"
#include "resources/InputManager.h"
#include "resources/Resources.h"
#include "states/TitleState.h"
#include "util/Logger.h"

Game *Game::sInstance;

Game::Game(std::string title, uint32_t width, uint32_t height)
    : mStoredState{nullptr} {
    if (sInstance != nullptr) {
        printf("Invalid call to Game constructor");
        exit(1);
    } else {
        sInstance = this;
    }

    int sdlErrorValue =
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if (sdlErrorValue != 0) {
        printf("%s\n%s\n", "Failed to init SDL", SDL_GetError());
        exit(1);
    }

    int availableLoaders = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    if (availableLoaders == 0) {
        printf("No available image loaders");
        exit(1);
    }

    Mix_Init(MIX_INIT_MP3);

    int mixErrorValue = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                                      MIX_DEFAULT_CHANNELS, 1024);
    if (mixErrorValue != 0) {
        printf("Failed to init SDL audio");
        exit(1);
    }

    Mix_AllocateChannels(CHANNELS_AMOUNT);

    // ISSO DEVERIA ESTAR NO ROTEIRO, PAREM DE DAR SUSTO NOS ALUNOS
    Mix_VolumeMusic(GAME_VOLUME);
    Mix_Volume(-1, GAME_VOLUME);

    mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (mWindow == nullptr) {
        printf("Failed to create SDL window");
        exit(1);
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == nullptr) {
        printf("Failed to create SDL renderer");
        exit(1);
    }

    int ttfInitError = TTF_Init();
    if (ttfInitError) {
        printf("Failed to init TTF");
        exit(1);
    }

    mStoredState = new TitleState();

    srand(time(NULL));
}

Game &Game::GetInstance() {
    if (sInstance == nullptr) {
        sInstance = new Game("Game", WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    return *sInstance;
}

void Game::Run() {
    uint32_t frameEnd = 0;

    mDeltaTime = 30.0;

    PushStored();

    mFrameStart = SDL_GetTicks();

    while (!mStateStack.empty() && !mStateStack.top()->QuitRequested()) {
        InputManager::Update();

        if (mStateStack.top()->PopRequested()) {
            mStateStack.pop();

            if (!mStateStack.empty()) {
                mStateStack.top()->Resume();
            } else if (mStoredState == nullptr) {
                break;
            }
        }

        PushStored();

        mStateStack.top()->Update(mDeltaTime);

        mStateStack.top()->Render();
        SDL_RenderPresent(mRenderer);

        SDL_Delay(30);

        frameEnd = SDL_GetTicks();

        mDeltaTime = (frameEnd - mFrameStart) / 1000.0;

        mFrameStart = frameEnd;
    }
}

Game::~Game() {
    if (mStoredState) {
        delete mStoredState;
    }

    Resources::ClearAll();

    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    SDL_Quit();
}
