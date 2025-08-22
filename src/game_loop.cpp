#include "game_loop.h"
#include "debug.h"

namespace cmulate
{

GameLoop::GameLoop(size_t width, size_t height, size_t resolution) :
  entities_{std::make_unique<EntityManager>()},
  location_system_{std::make_unique<LocationSystem>()},
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
  for (auto entity : entities_->entities())
  {
    DBG_MSG("looping over entitie") << entity << std::endl;
    location_system_->update(entities_, world_, entity, delta_time);
  }
  last_ = now_;
}

void GameLoop::limit(float time)
{
  limited_ = true;
  total_time_ = Duration(time);
}

} // namespace

