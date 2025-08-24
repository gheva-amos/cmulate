#ifndef CMULATE_WORLD_H__
#define CMULATE_WORLD_H__
#include <vector>
#include "components/tile.h"
#include "utils/grid.h"
#include "data_types.h"
#include <random>

namespace cmulate
{

class World
{
public:
  using Tiles = std::vector<Tile>;
  World(size_t width, size_t height, size_t resolution);
  size_t width() const { return width_; }
  Tiles operator[](size_t idx) const;
  Tiles& operator[](size_t idx);
  static World random(size_t width, size_t height, size_t resolution);
  static void random(World& world);
  void update(float delta_time);
  void move_entity(EntityManager::Entity entity, DataType x, DataType y);
  void add_entity(EntityManager::Entity entity, DataType x, DataType y);
  virtual void init();
private:
  size_t width_;
  size_t height_;
  std::vector<Tiles> world_;
  Grid entity_grid_;
  float time_;
  static std::random_device rd;
  static std::uniform_real_distribution<DataType> distribution;
};

} // namespace

#endif // CMULATE_WORLD_H__
