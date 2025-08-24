#include "graphics/color.h"

namespace cmulate
{

Color::Color(int r, int g, int b, int alpha) :
  r_{r}, g_{g}, b_{b}, alpha_{alpha}
{
}

void Color::set_color(Render* renderer)
{
}

} // namespace

