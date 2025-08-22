#include "components/position.h"

namespace cmulate
{

Position::Position(DataType x, DataType y, DataType z) :
  x_{x}, y_{y}, z_{z}
{
}

void Position::set(DataType x, DataType y, DataType z)
{
  x_ = x;
  y_ = y;
  z_ = z;
}

} // namespace
