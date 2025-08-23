#ifndef CMULATE_PHYSICS_SYSTEM_H__
#define CMULATE_PHYSICS_SYSTEM_H__
#include <memory>
#include "data_types.h"
#include "entities/entity_manager.h"

namespace cmulate
{

class PhysicsSystem
{
public:
  PhysicsSystem(DataType gravity);
  void update(std::unique_ptr<EntityManager>& entities,
      EntityManager::Entity entity, float delta_time);
  void apply_gravity(std::unique_ptr<EntityManager>& entities, DataType dt);
  void handle_collisions(std::unique_ptr<EntityManager>& entities,
      EntityManager::Entity entity, EntityManager::Entity other);
private:
  DataType gravity_;
};

} // namespace

#endif // CMULATE_PHYSICS_SYSTEM_H__
