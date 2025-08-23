#include "systems/physics_system.h"

namespace cmulate
{

PhysicsSystem::PhysicsSystem(DataType gravity) :
  gravity_{gravity}
{
}

void PhysicsSystem::update(std::unique_ptr<EntityManager>& entities,
    EntityManager::Entity entity, float delta_time)
{
  entities->speed_entity(entity, delta_time);
}

void PhysicsSystem::apply_gravity(std::unique_ptr<EntityManager>& entities, DataType dt)
{
  entities->apply_gravity(gravity_, dt);
}

void PhysicsSystem::handle_collisions(std::unique_ptr<EntityManager>& entities,
    EntityManager::Entity entity, EntityManager::Entity other)
{
  if (entities->collide(entity, other))
  {
  }
}

} // namespace

