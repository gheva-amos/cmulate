#include "graphics/graphics.h"
#include "render/render.h"
#include "debug.h"

namespace cmulate
{
void Graphics::render(Render* renderer)
{
  color_.set_color(renderer);
  do_render(renderer);
}

void Graphics::set_color(Color c)
{
  color_ = c;
}

} // namespace

