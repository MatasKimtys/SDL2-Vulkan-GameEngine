
#include "spdlog/spdlog.h"
#include "sdl_wrapper.hpp"

namespace SDLWrapper {

SDL::SDL(unsigned int screenWidth, unsigned int screenHeight)
    : screenWidth(screenWidth),
      screenHeight(screenHeight)
{
    initialiseSDL();
    window = createSDLWindow(
        "Vulkan Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth, 
        screenHeight,
        SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
    renderer = createSDLRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL::~SDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL::initialiseSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        spdlog::critical( "SDL_Init Error: {}", SDL_GetError());
        exit(-1);
    }
}

SDL_Window* SDL::createSDLWindow(const char *title, int x, int y, int w, int h, Uint32 flags) const {
    SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == nullptr) {
        spdlog::critical("SDL_CreateWindow Error: {}", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }
    return window;
}

SDL_Renderer* SDL::createSDLRenderer(SDL_Window* window, int index, Uint32 flags) const {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
    if (renderer == nullptr) {
        spdlog::critical("SDL_CreateRenderer Error: {}", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }
    return renderer;
}

SDL_Renderer* SDL::getRenderer() const {
    return renderer;
}

SDL_Window* SDL::getWindow() const {
    return window;
}

} // namespace SDLWrapper
