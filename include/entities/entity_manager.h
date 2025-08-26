#ifndef CMULATE_ENTITY_MANAGER_H__
#define CMULATE_ENTITY_MANAGER_H__
#include "utils/atom_table.h"
#include "components/position.h"
#include "components/velocity.h"
#include "components/acceleration.h"
#include "event/entity_event.h"
#include "event/event.h"
#include "event/trigger.h"
#include "graphics/color.h"
#include "render/render.h"
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <memory>
#include <mutex>

namespace cmulate
{

class EntityManager
{
public:
  using Entity = AtomTable::Atom;
  using Size = std::pair<DataType, DataType>;
  EntityManager();
  virtual ~EntityManager() = default;
  const std::string& entity_name(Entity entity);
  Entity add_entity(const std::string& name);
  void remve_entity(Entity entity);
  Entity operator[](size_t index) const;
  Entity at(size_t index) const;

  std::unordered_set<Entity>& entities() { return entities_; }
  std::unordered_map<Entity, Position>& positions() { return positions_; }
  std::unordered_map<Entity, Acceleration>& accelerations() { return accelerations_; }
  Position& location(Entity entity);
  Velocity& speed(Entity entity);
  Acceleration& acceleration(Entity entity);
  Size& size(Entity entity);
  Color& color(Entity entity);

  Position location(Entity entity) const;
  Velocity speed(Entity entity) const;
  Acceleration acceleration(Entity entity) const;
  Size size(Entity entity) const;
  Color color(Entity entity) const;

  bool move_entity(Entity entity, float dt, Position& ret);
  void move_entity(Entity entity, Position new_position);
  bool speed_entity(Entity entity, float dt);
  bool collide(Entity entity, Entity other);
  void apply_gravity(DataType gravity, DataType dt);

  void add_trigger(std::unique_ptr<Trigger> trigger);
  void process_triggers();

  void render(Render* renderer);

  virtual void handle_collision(Entity op1, Entity op2);
  virtual void init();

  void add_motion_event(std::vector<std::any>& args);
  void add_event_listener(EntityEvent::Type type, EventFunctor& functor);
  void process_events();

  bool bigger(Entity one, Entity other);
private:
  void init_events();
  AtomTable atoms_;
  std::unordered_set<Entity> entities_;
  std::unordered_set<EntityEvent::EventReference, EventHash, EventCompare> events_;
  std::unordered_map<Entity, Position> positions_;
  std::unordered_map<Entity, Velocity> velocities_;
  std::unordered_map<Entity, Acceleration> accelerations_;
  std::unordered_map<Entity, std::pair<DataType, DataType>> sizes_;
  std::unordered_map<Entity, Color> colors_;
  std::queue<std::unique_ptr<Trigger>> triggers_;
  EntityEvent collision_event_;
  EntityEvent motion_event_;
  std::mutex lock_;
};

} // namespace

#endif // CMULATE_ENTITY_MANAGER_H__
