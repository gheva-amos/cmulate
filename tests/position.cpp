#include <gtest/gtest.h>
#include "components/position.h"

using namespace cmulate;

TEST(PositionTestConstructor, CMulateTests)
{
  DataType x{5.5f}, y{34.f}, z{3.4f};
  Position p{x, y, z};
  EXPECT_NEAR(p.x(), x, 1e-9);
  EXPECT_NEAR(p.y(), y, 1e-9);
  EXPECT_NEAR(p.z(), z, 1e-9);
  DataType x1{3.5f}, y1{3.44f}, z1{8.3f};
  p.set(x1, y1, z1);
  EXPECT_NEAR(p.x(), x1, 1e-9);
  EXPECT_NEAR(p.y(), y1, 1e-9);
  EXPECT_NEAR(p.z(), z1, 1e-9);
  DataType x2{4.5f}, y2{6.74f}, z2{1.5f};
  p.x() = x2;
  p.y() = y2;
  p.z() = z2;
  EXPECT_NEAR(p.x(), x2, 1e-9);
  EXPECT_NEAR(p.y(), y2, 1e-9);
  EXPECT_NEAR(p.z(), z2, 1e-9);
}

