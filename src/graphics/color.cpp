#include "graphics/color.h"
#include "render/render.h"

namespace cmulate
{

Color::Color(int r, int g, int b, int alpha) :
  r_{r}, g_{g}, b_{b}, alpha_{alpha}
{
}

void Color::set_color(Render* renderer)
{
  renderer->set_color(r_, g_, b_, alpha_);
}

} // namespace

