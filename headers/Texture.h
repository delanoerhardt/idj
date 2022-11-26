#pragma once

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

typedef struct {
    SDL_Texture* sdlTexture;
    int width;
    int height;
} Texture;
