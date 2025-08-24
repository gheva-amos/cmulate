#ifndef CMULATE_RECT_H__
#define CMULATE_RECT_H__

#include "graphics/graphics.h"

namespace cmulate
{

class Render;

class Rect : public Graphics
{
public:
  Rect(int x, int y, int width, int height);
  void do_render(Render* renderer);

  int x() { return x_; };
  int y() { return y_; };
  int width() { return width_; };
  int height() { return height_; };

private:
  int x_;
  int y_;
  int width_;
  int height_;
};

} // namespace

#endif // CMULATE_RECT_H__
