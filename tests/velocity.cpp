#include <gtest/gtest.h>
#include "velocity.h"

using namespace cmulate;

TEST(VelocityTestConstructor, CMulateTests)
{
  DataType dx{5.5f}, dy{34.f}, dz{3.4f};
  Velocity v{dx, dy, dz};
  EXPECT_NEAR(v.dx(), dx, 1e-9);
  EXPECT_NEAR(v.dy(), dy, 1e-9);
  EXPECT_NEAR(v.dz(), dz, 1e-9);
  DataType x1{3.5f}, y1{3.44f}, z1{8.3f};
  v.set(x1, y1, z1);
  EXPECT_NEAR(v.dx(), x1, 1e-9);
  EXPECT_NEAR(v.dy(), y1, 1e-9);
  EXPECT_NEAR(v.dz(), z1, 1e-9);
  DataType x2{4.5f}, y2{6.74f}, z2{1.5f};
  v.dx() = x2;
  v.dy() = y2;
  v.dz() = z2;
  EXPECT_NEAR(v.dx(), x2, 1e-9);
  EXPECT_NEAR(v.dy(), y2, 1e-9);
  EXPECT_NEAR(v.dz(), z2, 1e-9);
}

