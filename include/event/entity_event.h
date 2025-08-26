#ifndef CMULATE_ENTITY_EVENT_H__
#define CMULATE_ENTITY_EVENT_H__

#include "event/event.h"

namespace cmulate
{

class EntityEvent : public Event
{
public:
  using EventReference = std::reference_wrapper<EntityEvent>;
  enum class Type
  {
    collision,
    unknown
  };
  EntityEvent(Type t);
  virtual EventId id() const override;
private:
  Type type_;
};

} // namespace

#endif // CMULATE_ENTITY_EVENT_H__
