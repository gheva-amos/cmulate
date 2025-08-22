#include <gtest/gtest.h>
#include "components/acceleration.h"

using namespace cmulate;

TEST(AccelerationTestConstructor, CMulateTests)
{
  DataType ax{5.5f}, ay{34.f}, az{3.4f};
  Acceleration a{ax, ay, az};
  EXPECT_NEAR(a.ax(), ax, 1e-9);
  EXPECT_NEAR(a.ay(), ay, 1e-9);
  EXPECT_NEAR(a.az(), az, 1e-9);
  DataType x1{3.5f}, y1{3.44f}, z1{8.3f};
  a.set(x1, y1, z1);
  EXPECT_NEAR(a.ax(), x1, 1e-9);
  EXPECT_NEAR(a.ay(), y1, 1e-9);
  EXPECT_NEAR(a.az(), z1, 1e-9);
  DataType x2{4.5f}, y2{6.74f}, z2{1.5f};
  a.ax() = x2;
  a.ay() = y2;
  a.az() = z2;
  EXPECT_NEAR(a.ax(), x2, 1e-9);
  EXPECT_NEAR(a.ay(), y2, 1e-9);
  EXPECT_NEAR(a.az(), z2, 1e-9);
}

