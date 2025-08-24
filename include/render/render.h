#ifndef CMULATE_RENDER_H__
#define CMULATE_RENDER_H__

#include <vector>
#include "graphics/line.h"
#include "graphics/rect.h"
#include "graphics/color.h"

namespace cmulate
{

class Render
{
public:
  virtual ~Render() = default;
  virtual void render_line(int x1, int y1, int x2, int y2) = 0;
  virtual void render_rect(int x1, int y1, int w, int h) = 0;
  virtual void set_color(int r, int g, int b, int alpha) = 0;

  virtual void render() = 0;

  void add_line(int x1, int y1, int x2, int y2);
  void add_rect(int x1, int y1, int w, int h);
  void add_rect(Rect& r);
protected:
  void render_entities();
private:
  std::vector<Line> lines_;
  std::vector<Rect> rects_;
};

} // namespace

#endif // CMULATE_RENDER_H__
