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

  int& red() { return r_; }
  int& green() { return g_; }
  int& blue() { return b_; }
  int& alpha() { return alpha_; }

  int red() const { return r_; }
  int green() const { return g_; }
  int blue() const { return b_; }
  int alpha() const { return alpha_; }

  void set_color(Render* renderer);
private:
  int r_;
  int g_;
  int b_;
  int alpha_;
};

} // namespace

#endif // CMULATE_COLOR_H__
