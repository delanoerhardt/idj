#include "Game.h"

#include <cstdlib>
#include <ctime>

#include "Constants.h"
#include "Resources.h"

Game *Game::sInstance;

Game::Game(std::string title, u_int32_t width, u_int32_t height) {
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
    Mix_VolumeMusic(16);
    Mix_Volume(-1, 32);

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

    mState = new State();

    srand(time(NULL));
}

Game &Game::GetInstance() {
    if (sInstance == nullptr) {
        sInstance = new Game("Game", 1024, 600);
    }

    return *sInstance;
}

SDL_Renderer *Game::GetRenderer() { return mRenderer; }

State &Game::GetState() { return *mState; }

void Game::Run() {
    while (!mState->QuitRequested()) {
        mState->Update(0);
        mState->Render();
        SDL_RenderPresent(mRenderer);

        SDL_Delay(30);
    }
}

Game::~Game() {
    delete mState;

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    SDL_Quit();
}
