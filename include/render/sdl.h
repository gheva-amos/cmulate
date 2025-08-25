#ifndef CMULATE_SDL_H__
#define CMULATE_SDL_H__

#include <SDL2/SDL.h>
#include "render/render.h"
#include <string>

namespace cmulate
{

class SDLRender : public Render
{
public:
  SDLRender(const std::string& title);
  virtual ~SDLRender();
  virtual void render() override;
  virtual bool go_on() override;
  virtual void render_line(int x1, int y1, int x2, int y2) override;
  virtual void render_rect(int x1, int y1, int w, int h) override;
  virtual void set_color(int r, int g, int b, int alpha) override;
private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

} // namespace

#endif // CMULATE_SDL_H__
