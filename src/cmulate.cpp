#include <iostream>
#include <random>
#include <sstream>
#include <cctype>
#include "game_loop.h"
#include "components/velocity.h"
#include "components/acceleration.h"
#define DEBUG
#include "debug.h"

using namespace cmulate;

class CollisionFunctor : public EventFunctor
{
public:
  virtual void operator()(std::vector<std::any>& args) override;
};

class CMulateLoop : public GameLoop
{
public:
  CMulateLoop(std::unique_ptr<EntityManager> entities, size_t width, size_t height, size_t resolution, DataType gravity=9.81f) :
    GameLoop{std::move(entities), width, height, resolution, gravity}
  {
    init();
  }
  virtual void init() override;
private:
};

class CMulateEntities : public EntityManager
{
public:
  CMulateEntities(size_t entity_count);
  virtual void init() override;
private:
  size_t entity_count_;
  static std::string random_string(size_t len);
  static std::random_device rd;
  static std::uniform_real_distribution<DataType> position_d;
  static std::uniform_real_distribution<DataType> acceleration_d;
  static std::uniform_real_distribution<DataType> size_d;
  static std::uniform_real_distribution<DataType> velo_d;
  static std::uniform_int_distribution<int> idistribution;
  static std::uniform_int_distribution<char> str_d;
  CollisionFunctor collision_handler_;
};

int main()
{
  CMulateLoop loop(std::make_unique<CMulateEntities>(12), 10, 10, 2, 3.1);
  GameLoop& looper{loop};

  looper.limit(10.0f);

  looper();
  return 0;
}

std::random_device CMulateEntities::rd;
std::uniform_real_distribution<DataType> CMulateEntities::position_d{0, 500};
std::uniform_real_distribution<DataType> CMulateEntities::acceleration_d{0, 5};
std::uniform_real_distribution<DataType> CMulateEntities::size_d{10, 50};
std::uniform_real_distribution<DataType> CMulateEntities::velo_d{5, 15};
std::uniform_int_distribution<int> CMulateEntities::idistribution{0, 255};
std::uniform_int_distribution<char> CMulateEntities::str_d;

void CMulateLoop::init()
{
  world()->random(*world());
  entities()->init();
}

CMulateEntities::CMulateEntities(size_t entity_count) :
  EntityManager(),
  entity_count_{entity_count}
{
}

std::string CMulateEntities::random_string(size_t len)
{
  std::mt19937 gen{rd()};
  std::stringstream ss;
  for (size_t i{0}; i < len; ++i)
  {
    char c(str_d(gen));
    if (std::isalnum(c))
    {
      ss << c;
    }
  }
  return ss.str();
}

void CollisionFunctor::operator()(std::vector<std::any>& args)
{
  EntityManager* entities = std::any_cast<EntityManager*>(args[0]);
  EntityManager::Entity op1 = std::any_cast<EntityManager::Entity>(args[1]);
  EntityManager::Entity op2 = std::any_cast<EntityManager::Entity>(args[2]);

  DBG_MSG("Collision ") << entities->entity_name(op1) << ' ' << entities->entity_name(op2) << std::endl;
}

void CMulateEntities::init()
{
  add_event_listener(EntityEvent::Type::collision, collision_handler_);
  for (size_t i{0}; i < entity_count_; ++i)
  {
    std::mt19937 gen{rd()};
    auto id{add_entity(random_string(7))};

    Position& pos = location(id);
    pos.x() = position_d(gen);
    pos.y() = position_d(gen);
    pos.z() = position_d(gen);
    Color& c = color(id);
    c.red() = idistribution(gen);
    c.blue() = idistribution(gen);
    c.green() = idistribution(gen);
    c.alpha() = 255;
    Acceleration& accel = acceleration(id);
    accel.ax() = acceleration_d(gen);
    accel.ay() = acceleration_d(gen);
    Velocity& velo = speed(id);
    velo.dx() = velo_d(gen);
    velo.dy() = velo_d(gen);

    Size& sz = size(id);
    sz.first = size_d(gen);
    sz.second = size_d(gen);
  }
}


