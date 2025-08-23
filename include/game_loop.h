#ifndef CMULATE_GAME_LOOP_H__
#define CMULATE_GAME_LOOP_H__
#include "entities/entity_manager.h"
#include "systems/location_system.h"
#include "systems/physics_system.h"
#include "world.h"
#include <chrono>
#include <memory>

namespace cmulate
{

class GameLoop
{
public:
  using Clock = std::chrono::high_resolution_clock;
  using Tick = std::chrono::time_point<Clock>;
  using Duration = std::chrono::duration<float>;
  GameLoop(size_t width, size_t height, size_t resolution, DataType gravity=9.81f);
  GameLoop(std::unique_ptr<EntityManager> em, size_t width, size_t height, size_t resolution, DataType gravity=9.81f);
  void operator()();
  void tick();
  void limit(float time);
private:
  std::unique_ptr<EntityManager> entities_;
  std::unique_ptr<LocationSystem> location_system_;
  std::unique_ptr<PhysicsSystem> physics_system_;
  std::unique_ptr<World> world_;
  Tick start_;
  Tick last_;
  Tick now_;

  Duration total_time_;
  bool limited_{false};
};

} // namespace

#endif // CMULATE_GAME_LOOP_H__
