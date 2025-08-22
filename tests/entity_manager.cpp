#include <gtest/gtest.h>
#include "entity_manager.h"

using namespace cmulate;

TEST(EntityManagerTestConstruction, CMulateTests)
{
  EntityManager em;
  std::string name1{"entity"};
  std::string name2{"entity"};
  auto e1{em.add_entity(name1)};
  auto e2{em.add_entity(name2)};
  EXPECT_EQ(e1, e2);
}

TEST(VelocityTests, CMulateTests)
{
  EntityManager em;
  std::string name1{"entity"};
  auto e1{em.add_entity(name1)};
  Velocity& v{em.speed(e1)};
  EXPECT_NEAR(v.dx(), 0, 1e-9);
  EXPECT_NEAR(v.dy(), 0, 1e-9);
  EXPECT_NEAR(v.dz(), 0, 1e-9);
  DataType dx{9.8f}, dy{0.4f}, dz{5.6f};
  v.dx() = dx;
  v.dy() = dy;
  v.dz() = dz;
  v = em.speed(e1);
  EXPECT_NEAR(v.dx(), dx, 1e-9);
  EXPECT_NEAR(v.dy(), dy, 1e-9);
  EXPECT_NEAR(v.dz(), dz, 1e-9);
}

TEST(LocationTests, CMulateTests)
{
  EntityManager em;
  std::string name1{"entity"};
  auto e1{em.add_entity(name1)};
  Position& p{em.location(e1)};
  EXPECT_NEAR(p.x(), 0, 1e-9);
  EXPECT_NEAR(p.y(), 0, 1e-9);
  EXPECT_NEAR(p.z(), 0, 1e-9);
  DataType dx{9.8f}, dy{0.4f}, dz{5.6f};
  p.x() = dx;
  p.y() = dy;
  p.z() = dz;
  p = em.location(e1);
  EXPECT_NEAR(p.x(), dx, 1e-9);
  EXPECT_NEAR(p.y(), dy, 1e-9);
  EXPECT_NEAR(p.z(), dz, 1e-9);
}
