#ifndef CMULATE_LOCATION_SYSTEM_H__
#define CMULATE_LOCATION_SYSTEM_H__
#include <memory>
#include "entities/entity_manager.h"
#include "world.h"

namespace cmulate
{

class LocationSystem
{
public:
  void update(std::unique_ptr<EntityManager>& entities,
      std::unique_ptr<World>& world,
      EntityManager::Entity entity, float delta_time);
private:
};

} // namespace

#endif // CMULATE_LOCATION_SYSTEM_H__
