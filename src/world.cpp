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
  for (size_t h{0}; h < height; ++h)
  {
    for (size_t w{0}; w < width; ++w)
    {
      DataType rand{distribution(gen)};
      if (rand < 0.7f)
      {
        ret[h][w].type() = Tile::Type::grass;
        ret[h][w].can_walk_through() = true;
      }
      else if (rand < 0.9f)
      {
        ret[h][w].type() = Tile::Type::water;
        ret[h][w].can_walk_through() = false;
      }
      else
      {
        ret[h][w].type() = Tile::Type::mountain;
        ret[h][w].can_walk_through() = false;
      }
    }
  }
  return ret;
}

} // namespace

