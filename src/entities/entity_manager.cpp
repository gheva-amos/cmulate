#include "entities/entity_manager.h"
#include "graphics/rect.h"
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

EntityManager::Entity EntityManager::operator[](size_t index) const
{
  return entities_[index];
}

EntityManager::Entity EntityManager::at(size_t index) const
{
  return entities_[index];
}

Position& EntityManager::location(Entity entity)
{
  return positions_[entity];
}

Velocity& EntityManager::speed(Entity entity)
{
  return velocities_[entity];
}

Acceleration& EntityManager::acceleration(Entity entity)
{
  return accelerations_[entity];
}

EntityManager::Size& EntityManager::size(Entity entity)
{
  return sizes_[entity];
}

Color& EntityManager::color(Entity entity)
{
  return colors_[entity];
}

Position EntityManager::location(Entity entity) const
{
  return positions_.at(entity);
}

Velocity EntityManager::speed(Entity entity) const
{
  return velocities_.at(entity);
}

Acceleration EntityManager::acceleration(Entity entity) const
{
  return accelerations_.at(entity);
}

EntityManager::Size EntityManager::size(Entity entity) const
{
  return sizes_.at(entity);
}

Color EntityManager::color(Entity entity) const
{
  return colors_.at(entity);
}

bool EntityManager::move_entity(Entity entity, float dt, Position& ret)
{
  if (velocities_.count(entity) && positions_.count(entity))
  {
    Position& pos{location(entity)};
    Velocity& vel{speed(entity)};
    pos.x() += vel.dx() * dt;
    pos.y() += vel.dy() * dt;
    pos.z() += vel.dz() * dt;

    ret = pos;
    return true;
  }
  return false;
}

bool EntityManager::speed_entity(Entity entity, float dt)
{
  if (accelerations().count(entity))
  {
    Acceleration& accel{acceleration(entity)};
    speed(entity).dx() += accel.ax() * dt;
    speed(entity).dy() += accel.ay() * dt;
    speed(entity).dz() += accel.az() * dt;
    return true;
  }
  return false;
}

bool EntityManager::collide(Entity entity, Entity other)
{
  if (sizes_.count(entity) && sizes_.count(other))
  {
    Position p1{positions_[entity]}, p2{positions_[other]};
    Size s1{sizes_[entity]}, s2{sizes_[other]};

    return !((p1.x() + s1.first <= p2.x() || p2.x() + s2.first <= p1.x()) ||
          (p1.y() + s1.second <= p2.y() || p2.y() + s2.second <= p1.y())
      );
  }
  return false;
}

void EntityManager::apply_gravity(DataType gravity, DataType dt)
{
  for (auto& [_, accel] : accelerations_)
  {
    accel.ay() += gravity * dt;
  }
}

void EntityManager::add_trigger(std::unique_ptr<Trigger> trigger)
{
  triggers_.push(std::move(trigger));
}

void EntityManager::process_triggers()
{
  while (!triggers_.empty())
  {
    auto trigger{std::move(triggers_.front())};
    triggers_.pop();
    trigger->trigger();
  }
}

void EntityManager::render(Render* renderer)
{
  for (auto entity : entities_)
  {
    if (colors_.count(entity) && positions_.count(entity) && sizes_.count(entity))
    {
      Position& pos{positions_[entity]};
      Size size{sizes_[entity]};
      Rect tmp{
        static_cast<int>(pos.x()),
        static_cast<int>(pos.y()),
        static_cast<int>(size.first),
        static_cast<int>(size.second)};
      tmp.set_color(colors_[entity]);
      renderer->add_rect(tmp);
    }
  }
}

void EntityManager::handle_collision(Entity op1, Entity op2)
{
}

void EntityManager::init()
{
}

} // namespace
