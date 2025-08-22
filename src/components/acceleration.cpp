#include "components/acceleration.h"

namespace cmulate
{
Acceleration::Acceleration(DataType ax, DataType ay, DataType az) :
  ax_{ax}, ay_{ay}, az_{az}
{
}

void Acceleration::set(DataType ax, DataType ay, DataType az)
{
  ax_ = ax;
  ay_ = ay;
  az_ = az;
}

} // namespace

