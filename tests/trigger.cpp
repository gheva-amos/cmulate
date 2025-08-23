#include <gtest/gtest.h>
#include <string>
#include "event/functor.h"
#include "event/trigger.h"
#include "entities/entity_manager.h"
#include "debug.h"

using namespace cmulate;

class TriggerTestFunctor : public Functor
{
public:
  virtual std::string hash_seed() const override
  {
    return "Test Functor";
  }
  virtual size_t hash() const override
  {
    return 123;
  }
  virtual void operator()(std::unique_ptr<EntityManager>& em, EntityManager::Entity left,
      EntityManager::Entity right)
  {
    left_ = left;
    right_ = right;
  }
  EntityManager::Entity left() { return left_; }
  EntityManager::Entity right() { return right_; }
private:
  EntityManager::Entity left_{0}, right_{0};
};

class TestTrigger : public Trigger
{
public:
  TestTrigger(std::unique_ptr<EntityManager>& em) :
    entities_{em}
  {
  }

  void add_left_entity(EntityManager::Entity entity)
  {
    left_ = entity;
  }

  void add_right_entity(EntityManager::Entity entity)
  {
    right_ = entity;
  }
protected:
  virtual void do_trigger(Functor& func) override
  {
    TriggerTestFunctor& functor = dynamic_cast<TriggerTestFunctor&>(func);
    functor(entities_, left_, right_);
  }
  std::string left() { return entities_->entity_name(left_); }
  std::string right() { return entities_->entity_name(right_); }
private:
  std::unique_ptr<EntityManager>& entities_;
  EntityManager::Entity left_, right_;
};

TEST(TriggerSimple, CMulateTests)
{
  std::unique_ptr<EntityManager> em{std::make_unique<EntityManager>()};
  TestTrigger tester{em};
  std::string first{"First Entity"};
  std::string second{"Second Entity"};
  EntityManager::Entity left{em->add_entity(first)}, right{em->add_entity(second)};
  tester.add_left_entity(left);
  tester.add_right_entity(right);
  TriggerTestFunctor func;
  tester.add_function(func);
  tester.trigger();
  EXPECT_EQ(func.left(), left);
  EXPECT_EQ(func.right(), right);
}

