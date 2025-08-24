#include "world.h"

namespace cmulate
{
std::random_device World::rd{};
std::uniform_real_distribution<DataType> World::distribution{0.0f, 1.0f};

World::World(size_t width, size_t height, size_t resolution) :
  width_{width}, height_{height},
  world_{height, Tiles{width}},
  entity_grid_{width, height, resolution},
  time_{0.0f}
{
}

World::Tiles World::operator[](size_t idx) const
{
  return world_.at(idx);
}

World::Tiles& World::operator[](size_t idx)
{
  return world_[idx];
}

void World::update(float delta_time)
{
  time_ += delta_time;
}

void World::move_entity(EntityManager::Entity entity, DataType x, DataType y)
{
  entity_grid_.move_entity(entity, x, y);
}

void World::add_entity(EntityManager::Entity entity, DataType x, DataType y)
{
  entity_grid_.add_entity(entity, x, y);
}

World World::random(size_t width, size_t height, size_t resolution)
{
  std::mt19937 gen{rd()};
  World ret{width, height, resolution};
  random(ret);
  return ret;
}

void World::random(World& world)
{
  std::mt19937 gen{rd()};
  for (size_t h{0}; h < world.height_; ++h)
  {
    for (size_t w{0}; w < world.width_; ++w)
    {
      DataType rand{distribution(gen)};
      if (rand < 0.7f)
      {
        world[h][w].type() = Tile::Type::grass;
        world[h][w].can_walk_through() = true;
      }
      else if (rand < 0.9f)
      {
        world[h][w].type() = Tile::Type::water;
        world[h][w].can_walk_through() = false;
      }
      else
      {
        world[h][w].type() = Tile::Type::mountain;
        world[h][w].can_walk_through() = false;
      }
    }
  }
}

void World::init()
{
}

} // namespace

