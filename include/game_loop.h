#ifndef CMULATE_GAME_LOOP_H__
#define CMULATE_GAME_LOOP_H__
#include "entities/entity_manager.h"
#include "systems/location_system.h"
#include "systems/physics_system.h"
#include "render/render.h"
#include "world.h"
#include <chrono>
#include <memory>
#include <atomic>
#include <thread>

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
  virtual ~GameLoop();
  void operator()();
  void tick();
  void limit(float time);

  virtual void init();

  EntityManager::Entity add_entity(const std::string& name, Position p, Color c, std::pair<DataType, DataType>& size);
  std::unique_ptr<EntityManager>& entities();
  std::unique_ptr<World>& world();
  void event_processor();
private:
  std::unique_ptr<EntityManager> entities_;
  std::unique_ptr<LocationSystem> location_system_;
  std::unique_ptr<PhysicsSystem> physics_system_;
  std::unique_ptr<World> world_;
  std::unique_ptr<Render> renderer_;
  Tick start_;
  Tick last_;
  Tick now_;

  std::atomic<bool> events_running_;
  std::thread event_processor_;
  Duration total_time_;
  bool limited_{false};
};

} // namespace

#endif // CMULATE_GAME_LOOP_H__
