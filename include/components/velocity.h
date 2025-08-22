#ifndef CMULATE_VELOCITY_H__
#define CMULATE_VELOCITY_H__
#include "data_types.h"

namespace cmulate
{

class Velocity
{
public:
  Velocity() = default;
  Velocity(DataType dx, DataType dy, DataType dz);
  Velocity(const Velocity& other) = default;

  Velocity& operator=(const Velocity&) = default;
  DataType dx() const { return dx_; }
  DataType dy() const { return dy_; }
  DataType dz() const { return dz_; }
  DataType& dx() { return dx_; }
  DataType& dy() { return dy_; }
  DataType& dz() { return dz_; }
  void set(DataType dx, DataType dy, DataType dz);
private:
  DataType dx_;
  DataType dy_;
  DataType dz_;
};


} // namespace

#endif //  CMULATE_VELOCITY_H__
