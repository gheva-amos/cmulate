#include <iostream>
#include "game_loop.h"
#include "components/velocity.h"
#include "components/acceleration.h"

using namespace cmulate;

int main()
{
  GameLoop looper(10, 10, 2, 3.1);
  Position p{50.0, 50.0, 0.0};
  Color c{0, 0, 0, 255};
  std::pair<float, float> size = std::make_pair(100, 50);

  auto id = looper.add_entity("bear", p, c, size);
  Velocity& speed{looper.entities()->speed(id)};
  speed.dx() = 2;
  speed.dy() = 5;
  Acceleration& acceleration{looper.entities()->acceleration(id)};
  acceleration.ax() = 2;
  acceleration.ay() = 5;
  looper.limit(10.0f);

  looper();
  return 0;
}
