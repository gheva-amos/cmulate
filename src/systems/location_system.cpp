#include "systems/location_system.h"

namespace cmulate
{

void LocationSystem::update(std::unique_ptr<EntityManager>& entities,
    std::unique_ptr<World>& world,
    EntityManager::Entity entity, float delta_time)
{
  if (entities->positions().count(entity) && entities->positions().count(entity))
  {
    entities->location(entity).x() += entities->speed(entity).dx() * delta_time;
    entities->location(entity).y() += entities->speed(entity).dy() * delta_time;
    entities->location(entity).z() += entities->speed(entity).dz() * delta_time;
    world->move_entity(entity, entities->location(entity).x(),
        entities->location(entity).y());
  }
}

} // namespace

