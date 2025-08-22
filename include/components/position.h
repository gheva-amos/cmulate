#ifndef CMULATE_POSITION_H__
#define CMULATE_POSITION_H__
#include "data_types.h"

namespace cmulate
{

class Position
{
public:
  Position() = default;
  Position(DataType x, DataType y, DataType z);
  Position(const Position& other) = default;

  Position& operator=(const Position&) = default;

  DataType x() const { return x_; }
  DataType y() const { return y_; }
  DataType z() const { return z_; }
  DataType& x() { return x_; }
  DataType& y() { return y_; }
  DataType& z() { return z_; }
  void set(DataType x, DataType y, DataType z);
private:
  DataType x_;
  DataType y_;
  DataType z_;
};

} // namespace

#endif // CMULATE_POSITION_H__
