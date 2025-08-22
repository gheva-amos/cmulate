#include "velocity.h"

namespace cmulate
{

Velocity::Velocity(DataType dx, DataType dy, DataType dz) :
  dx_{dx}, dy_{dy}, dz_{dz}
{
}

void Velocity::set(DataType dx, DataType dy, DataType dz)
{
  dx_ = dx;
  dy_ = dy;
  dz_ = dz;
}

} // namespace
