#ifndef CMULATE_ENTITY_MANAGER_H__
#define CMULATE_ENTITY_MANAGER_H__
#include "utils/atom_table.h"
#include "components/position.h"
#include "components/velocity.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace cmulate
{

class AtomTable;

class EntityManager
{
public:
  using Entity = AtomTable::Atom;
  EntityManager();
  const std::string& entity_name(Entity entity);
  Entity add_entity(const std::string& name);

  std::vector<Entity> entities() { return entities_; }
  std::unordered_map<Entity, Position> positions() { return positions_; }
  Position& location(Entity entity);
  Velocity& speed(Entity entity);
  Position location(Entity entity) const;
  Velocity speed(Entity entity) const;
private:
  AtomTable atoms_;
  std::vector<Entity> entities_;
  std::unordered_set<Entity> all_entities_;
  std::unordered_map<Entity, Position> positions_;
  std::unordered_map<Entity, Velocity> velocities_;
};

} // namespace

#endif // CMULATE_ENTITY_MANAGER_H__
