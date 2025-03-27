#include <SDL2/SDL.h>
#include <memory>
#include <SDL2/SDL_vulkan.h>

namespace SDLWrapper {
class SDL {
private:
    unsigned int screenWidth;
    unsigned int screenHeight;
    // SDL_Renderer* renderer;
    SDL_Window* window;
    
public:

public:
    SDL(unsigned int screenWidth, unsigned int screenHeight);
    ~SDL();
    void initialiseSDL();
    SDL_Window* createSDLWindow(const char *title, int x, int y, int w, int h, Uint32 flags) const;
    SDL_Renderer* createSDLRenderer(SDL_Window *window, int index, Uint32 flags) const;
    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    std::pair<unsigned int, unsigned int> getWindowSize() const;
};
}
