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

size_t rand_up_to(int limit)
{
  static thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<size_t> dist(1, limit);
  return dist(gen);
}

class CollisionFunctor : public EventFunctor
{
public:
  virtual void operator()(std::vector<std::any>& args) override;
};

class MotionFunctor : public EventFunctor
{
public:
  MotionFunctor(size_t width, size_t height);
  virtual void operator()(std::vector<std::any>& args) override;
private:
  size_t width_;
  size_t height_;
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
  CMulateEntities(size_t entity_count, size_t width, size_t height);
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
  MotionFunctor motion_handler_;
};

int main()
{
  size_t width{500};
  size_t height{500};
  CMulateLoop loop(std::make_unique<CMulateEntities>(12, width, height), width, height, 2, 3.1);
  GameLoop& looper{loop};

  looper.limit(100.0f);

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
  for (auto entity : entities()->entities())
  {
    Position p{entities()->location(entity)};
    world()->add_entity(entity, p.x(), p.y());
  }
}

CMulateEntities::CMulateEntities(size_t entity_count, size_t width, size_t height) :
  EntityManager(),
  entity_count_{entity_count},
  motion_handler_{width, height}
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
  
  EntityManager::Entity remainig{op1};
  Color c;
  if (entities->bigger(op1, op2))
  {
    c = entities->color(op2);
    entities->remve_entity(op2);
  }
  else
  {
    c = entities->color(op1);
    remainig = op2;
    entities->remve_entity(op1);
  }

  entities->color(remainig).red() += c.red();
  entities->color(remainig).green() += c.green();
  entities->color(remainig).blue() += c.blue();

  entities->speed(remainig).dx() *= -1;
  entities->speed(remainig).dy() *= -1;
}

MotionFunctor::MotionFunctor(size_t w, size_t h) :
  width_{w}, height_{h}
{
}

void MotionFunctor::operator()(std::vector<std::any>& args)
{
  EntityManager* entities = std::any_cast<EntityManager*>(args[0]);
  World* world = std::any_cast<World*>(args[1]);
  EntityManager::Entity entity = std::any_cast<EntityManager::Entity>(args[2]);
  DataType x = std::any_cast<DataType>(args[3]);
  DataType y = std::any_cast<DataType>(args[4]);
  if (world->out_of_this(x, y))
  {
    Position p{rand_up_to(width_), rand_up_to(height_), 0.0};
    entities->move_entity(entity, p);
  }
  else
  {
    world->move_entity(entity, x, y);
  }
}

void CMulateEntities::init()
{
  add_event_listener(EntityEvent::Type::collision, collision_handler_);
  add_event_listener(EntityEvent::Type::motion, motion_handler_);
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


