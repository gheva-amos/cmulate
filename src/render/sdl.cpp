#include "render/sdl.h"
#include "debug.h"

namespace cmulate
{

SDLRender::SDLRender(const std::string& title) :
  window_{nullptr}, renderer_{nullptr}
{
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    DBG_MSG("SDL error ") << SDL_GetError() << std::endl;
    throw std::runtime_error("Could not init SDL");
  }
  window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
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

void SDLRender::render()
{
}

void SDLRender::render_line(int x1, int y1, int x2, int y2)
{
  SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
}

void SDLRender::render_rect(int x1, int y1, int w, int h)
{
  SDL_Rect rect{x1, y1, w, h};
  SDL_RenderFillRect(renderer_, &rect);

}

void SDLRender::set_color(int r, int g, int b, int alpha)
{
  SDL_SetRenderDrawColor(renderer_, r, g, b, alpha);
}

SDLRender::~SDLRender()
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

} // namespace

