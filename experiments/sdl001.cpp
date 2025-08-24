#include <SDL2/SDL.h>
#include <stdexcept>
#define DEBUG
#include "debug.h"

using cmulate::get_log_stream;
class Renderer
{
public:
  Renderer() :
    window_{nullptr}, renderer_{nullptr}
  {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      DBG_MSG("SDL error ") << SDL_GetError() << std::endl;
      throw std::runtime_error("Could not init SDL");
    }
    window_ = SDL_CreateWindow("Experiment 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    if (!window_)
    {
      DBG_MSG("SDL error ") << SDL_GetError() << std::endl;
      throw std::runtime_error("Could not create a window");
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer_)
    {
      DBG_MSG("SDL error ") << SDL_GetError() << std::endl;
      throw std::runtime_error("Could not create a renderer");
    }
  }
  virtual ~Renderer()
  {
    if (renderer_ != nullptr)
    {
      SDL_DestroyRenderer(renderer_);
    }
    if (window_ != nullptr)
    {
      SDL_DestroyWindow(window_);
    }
    SDL_Quit();
  }

  bool handle_sdl_events()
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        return false;
      }
    }
    return true;
  }
  void render()
  {

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);//  Black background
    SDL_RenderClear(renderer_);  // Draw grid
    SDL_SetRenderDrawColor(renderer_, 100, 100, 100,  255);// Gray lines

  }
private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

int main()
{
  Renderer renderer;

  while (renderer.handle_sdl_events())
  {
    renderer.render();
    SDL_Delay(16);
  }

  return 0;
}

