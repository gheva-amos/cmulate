#include "grid.h"
#include <algorithm>

namespace cmulate
{

Grid::Grid(size_t width, size_t height, size_t cell) :
  width_{width}, cell_{cell},
  y_factor_{width / cell}, x_factor_{height / cell}
{
}

size_t Grid::bucket(DataType x, DataType y) const
{
  int x_{static_cast<int>(x / cell_)};
  int y_{static_cast<int>(y / cell_)};
  return x_ * x_factor_ + y_ * y_factor_;
}

void Grid::add_entity(EntityManager::Entity entity, DataType x, DataType y)
{
  if (entitys_bucket_.count(entity))
  {
    size_t current{entitys_bucket_[entity]};
    size_t next{bucket(x, y)};
    if (current == next)
    {
      return;
    }
    move_entity(entity, current, next);
    return;
  }
  size_t idx{bucket(x, y)};
  buckets_[idx].push_back(entity);
}

void Grid::move_entity(EntityManager::Entity entity, DataType x, DataType y)
{
  size_t current{entitys_bucket_[entity]};
  size_t next{bucket(x, y)};
  if (current == next)
  {
    return;
  }
  move_entity(entity, current, next);
}

void Grid::move_entity(EntityManager::Entity entity, size_t from, size_t to)
{
  std::vector<EntityManager::Entity>& current{buckets_[from]};
  current.erase(std::remove(current.begin(), current.end(), entity), current.end());
  buckets_[to].push_back(entity);
  entitys_bucket_[entity] = to;
}

std::vector<EntityManager::Entity>& Grid::contents(DataType x, DataType y)
{
  size_t idx{bucket(x, y)}; 
  return buckets_[idx];
}

} // namespace

