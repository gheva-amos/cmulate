#include "entities/entity_manager.h"
#include "debug.h"

namespace cmulate
{

EntityManager::EntityManager() :
  atoms_{AtomTable{}}
{
}

const std::string& EntityManager::entity_name(Entity entity)
{
  return atoms_.value(entity);
}

EntityManager::Entity EntityManager::add_entity(const std::string& name)
{
  Entity entity{atoms_.intern(name)};
  if (all_entities_.find(entity) == all_entities_.end())
  {
    all_entities_.insert(entity);
    entities_.push_back(entity);
  }
  return entity;
}

Position& EntityManager::location(Entity entity)
{
  if (!positions_.count(entity))
  {
    positions_.insert(std::make_pair(entity, Position{0, 0, 0}));
  }
  return positions_[entity];
}

Velocity& EntityManager::speed(Entity entity)
{
  if (!velocities_.count(entity))
  {
    velocities_.insert(std::make_pair(entity, Velocity{0, 0, 0}));
  }
  return velocities_[entity];
}

Position EntityManager::location(Entity entity) const
{
  return positions_.at(entity);
}

Velocity EntityManager::speed(Entity entity) const
{
  return velocities_.at(entity);
}

} // namespace
