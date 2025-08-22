#ifndef CMULATE_ACCELERATION_H__
#define CMULATE_ACCELERATION_H__
#include "data_types.h"

namespace cmulate
{

class Acceleration
{
public:
  Acceleration() = default;
  Acceleration(DataType ax, DataType ay, DataType az);
  Acceleration(const Acceleration& other) = default;

  Acceleration& operator=(const Acceleration&) = default;

  DataType ax() const { return ax_; }
  DataType ay() const { return ay_; }
  DataType az() const { return az_; }
  DataType& ax() { return ax_; }
  DataType& ay() { return ay_; }
  DataType& az() { return az_; }
  void set(DataType ax, DataType ay, DataType az);
private:
  DataType ax_;
  DataType ay_;
  DataType az_;
};

} // namespace

#endif // CMULATE_ACCELERATION_H__
