#ifndef CMULATE_LINE_H__
#define CMULATE_LINE_H__
#include <memory>
#include "graphics/graphics.h"

namespace cmulate
{

class Render;

class Line : public Graphics
{
public:
  Line(int from_x, int from_y, int to_x, int to_y);

  void do_render(Render* renderer) override;

private:
  int from_x_;
  int from_y_;
  int to_x_;
  int to_y_;
};

} // namespace

#endif // CMULATE_LINE_H__
