#ifndef CMULATE_COLOR_H__
#define CMULATE_COLOR_H__

namespace cmulate
{

class Render;

class Color
{
public:
  Color() = default;
  Color(int r, int g, int b, int alpha);
  void set_color(Render* renderer);
private:
  int r_;
  int g_;
  int b_;
  int alpha_;
};

} // namespace

#endif // CMULATE_COLOR_H__
