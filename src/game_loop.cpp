#include "game_loop.h"
#include "debug.h"

namespace cmulate
{

GameLoop::GameLoop(size_t width, size_t height, size_t resolution, DataType gravity) :
  entities_{std::make_unique<EntityManager>()},
  location_system_{std::make_unique<LocationSystem>()},
  physics_system_{std::make_unique<PhysicsSystem>(gravity)},
  world_{std::make_unique<World>(width, height, resolution)}
{
}

void GameLoop::operator()()
{
  last_ = start_ = Clock::now();
  while (true)
  {
    tick();
    if (limited_)
    {
      Duration dt = now_ - start_;
      if (dt > total_time_)
      {
        break;
      }
    }
  }
}

void GameLoop::tick()
{
  now_ = Clock::now();
  Duration dt = now_ - last_;
  float delta_time = dt.count();
  world_->update(delta_time);
  physics_system_->apply_gravity(entities_, delta_time);
  size_t j{0};
  for (auto entity : entities_->entities())
  {
    DBG_MSG("looping over entitie") << entity << std::endl;
    physics_system_->update(entities_, entity, delta_time);
    location_system_->update(entities_, world_, entity, delta_time);
    ++j;
    for (size_t k{j}; k < entities_->entities().size(); ++k)
    {
      physics_system_->handle_collisions(entities_, entity, entities_->at(k));
    }
  }
  last_ = now_;
}

void GameLoop::limit(float time)
{
  limited_ = true;
  total_time_ = Duration(time);
}

} // namespace

