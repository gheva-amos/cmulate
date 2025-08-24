#ifndef CMULATE_GRAPHICS_H__
#define CMULATE_GRAPHICS_H__

#include "graphics/color.h"
namespace cmulate
{

class Render;

class Graphics
{
public:
  virtual ~Graphics() = default;
  virtual void render(Render* renderer);
  void set_color(Color c);
  Color color() { return color_; }
protected:
  virtual void do_render(Render* renderer) = 0;
  Color color_{0, 0, 0, 255};
};

} // namespace

#endif // CMULATE_GRAPHICS_H__
