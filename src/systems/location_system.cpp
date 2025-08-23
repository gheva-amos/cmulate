#include "systems/location_system.h"

namespace cmulate
{

void LocationSystem::update(std::unique_ptr<EntityManager>& entities,
    std::unique_ptr<World>& world,
    EntityManager::Entity entity, float delta_time)
{
  Position tmp;
  if (entities->move_entity(entity, delta_time, tmp))
  {
    world->move_entity(entity, tmp.x(), tmp.y());
  }
}

} // namespace

