#include "render/render.h"

namespace cmulate
{

void Render::add_line(int x1, int y1, int x2, int y2)
{
  lines_.emplace_back(x1, y1, x2, y2);
}

void Render::add_rect(int x1, int y1, int w, int h)
{
  rects_.emplace_back(x1, y1, w, h);
}

void Render::render_entities()
{
  for (auto line : lines_)
  {
    line.render(this);
  }
  for (auto rect : rects_)
  {
    rect.render(this);
  }
}

} // namespace

