#include <gtest/gtest.h>
#include "event/event.h"
#include "entities/entity_manager.h"
#include "debug.h"

using namespace cmulate;

class TestEvent : public Event
{
public:
  TestEvent(EventId i) : id_{i} {}
  virtual EventId id() const override { return id_; }
private:
  EventId id_;
};

class TestFunctor : public EventFunctor
{
public:
  virtual void operator()(std::vector<std::any>& args) override
  {
    last_ = std::any_cast<EntityManager::Entity>(args[0]);
  }
  Event::EventId last_event() const { return last_; }
  virtual size_t hash() const override
  {
    return EventFunctor::hash() + 3;
  }
private:
  Event::EventId last_{0};
};

TEST(EventNotification, CMulateTests)
{
  Event::EventId id{42};
  TestEvent te{id};
  TestFunctor func;
  te.add_listener(func);
  std::vector<std::any> args;
  args.push_back(id);
  te.push_args(args);
  te.notify();
  EXPECT_EQ(func.last_event(), id);
}

