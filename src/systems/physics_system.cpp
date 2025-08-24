#include "systems/physics_system.h"
#include "debug.h"

namespace cmulate
{

class CollisionFunctor : public Functor
{
public:
  virtual void operator()() {}
  virtual std::string hash_seed() const override { return "Collision functor"; }
};

class CollisionTrigger : public Trigger
{
public:
  CollisionTrigger(
    std::unique_ptr<EntityManager>& em,
    EntityManager::Entity op1,
    EntityManager::Entity op2) :
    entities_{em}, op1_{op1}, op2_{op2}
  {
    add_function(func_);
  }
protected:
  virtual void do_trigger(Functor& func) override
  {
    entities_->handle_collision(op1_, op2_);
  }
private:
  std::unique_ptr<EntityManager>& entities_;
  EntityManager::Entity op1_;
  EntityManager::Entity op2_;
  CollisionFunctor func_;
};

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
    entities->add_trigger(std::make_unique<CollisionTrigger>(entities, entity, other));
  }
}

} // namespace

