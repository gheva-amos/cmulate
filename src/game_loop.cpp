#include "game_loop.h"
#include "debug.h"
#include "render/sdl.h"
#include <thread>

namespace cmulate
{

GameLoop::GameLoop(size_t width, size_t height, size_t resolution, DataType gravity) :
  entities_{std::make_unique<EntityManager>()},
  location_system_{std::make_unique<LocationSystem>()},
  physics_system_{std::make_unique<PhysicsSystem>(gravity)},
  world_{std::make_unique<World>(width, height, resolution)},
  renderer_{std::make_unique<SDLRender>(width, height, "CMulate")}
{
}

GameLoop::GameLoop(std::unique_ptr<EntityManager> em,
    size_t width, size_t height, size_t resolution, DataType gravity) :
  entities_{std::move(em)},
  location_system_{std::make_unique<LocationSystem>()},
  physics_system_{std::make_unique<PhysicsSystem>(gravity)},
  world_{std::make_unique<World>(width, height, resolution)},
  renderer_{std::make_unique<SDLRender>(width, height, "CMulate")}
{
}

GameLoop::~GameLoop()
{
  if (events_running_.exchange(false))
  {
    if (event_processor_.joinable())
    {
      event_processor_.join();
    }
  }
}

void GameLoop::operator()()
{
  events_running_.store(true, std::memory_order_release);
  event_processor_ = std::thread([this] { 
      event_processor();
      });
  last_ = start_ = Clock::now();
  while (renderer_->go_on())
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
    auto wake = now_ + std::chrono::milliseconds(16);
    std::this_thread::sleep_until(wake);
  }
  if (events_running_.exchange(false))
  {
    if (event_processor_.joinable())
    {
      event_processor_.join();
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
  std::vector<EntityManager::Entity> entities{entities_->entities().begin(), entities_->entities().end()};
  for (auto entity : entities)
  {
    DBG_MSG("looping over entitie ") << entity << std::endl;
    physics_system_->update(entities_, entity, delta_time);
    location_system_->update(entities_, world_, entity, delta_time);
    ++j;
    for (size_t k{j}; k < entities.size(); ++k)
    {
      physics_system_->handle_collisions(entities_, entity, entities.at(k));
    }
  }
  entities_->process_triggers();
  entities_->render(renderer_.get());
  renderer_->render();
  last_ = now_;
}

void GameLoop::limit(float time)
{
  limited_ = true;
  total_time_ = Duration(time);
}

EntityManager::Entity GameLoop::add_entity(const std::string& name, Position p, Color c,
    std::pair<DataType, DataType>& size)
{
  auto id = entities_->add_entity(name);
  entities_->color(id) = c;
  entities_->size(id).first = size.first;
  entities_->size(id).second = size.second;
  entities_->location(id) = p;
  return id;
}

std::unique_ptr<EntityManager>& GameLoop::entities()
{
  return entities_;
}

std::unique_ptr<World>& GameLoop::world()
{
  return world_;
}

void GameLoop::event_processor()
{
  while (events_running_.load(std::memory_order_acquire))
  {
    entities_->process_events();
  }
}

} // namespace

