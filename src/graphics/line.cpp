#include "graphics/line.h"
#include "render/render.h"

namespace cmulate
{
Line::Line(int from_x, int from_y, int to_x, int to_y) :
  from_x_{from_x}, from_y_{from_y}, to_x_{to_x}, to_y_{to_y}
{
}

void Line::do_render(Render* renderer)
{
  renderer->render_line(from_x_, from_y_, to_x_, to_y_);
}

} // namespace

