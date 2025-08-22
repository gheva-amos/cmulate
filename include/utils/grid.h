#ifndef CMULATE_GRID_H__
#define CMULATE_GRID_H__
#include <unordered_map>
#include <vector>
#include "entities/entity_manager.h"
#include "data_types.h"

namespace cmulate
{

class Grid
{
public:
  Grid(size_t width, size_t height, size_t cell);
  void add_entity(EntityManager::Entity entity, DataType x, DataType y);
  void move_entity(EntityManager::Entity entity, DataType x, DataType y);
  std::vector<EntityManager::Entity>& contents(DataType x, DataType y);
private:
  size_t bucket(DataType x, DataType y) const;
  void move_entity(EntityManager::Entity entity, size_t from, size_t to);
  std::unordered_map<size_t, std::vector<EntityManager::Entity>> buckets_;
  std::unordered_map<EntityManager::Entity, size_t> entitys_bucket_;
  size_t width_;
  size_t height_;
  size_t cell_;
  size_t y_factor_;
  size_t x_factor_;
};

} // namespace

#endif // CMULATE_GRID_H__
