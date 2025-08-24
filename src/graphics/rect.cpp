#include "graphics/rect.h"
#include "render/render.h"

namespace cmulate
{
Rect::Rect(int x, int y, int width, int height) :
  x_{x}, y_{y}, width_{width}, height_{height}
{
}

void Rect::do_render(Render* renderer)
{
  renderer->render_rect(x_, y_, width_, height_);
}

} // namespace

