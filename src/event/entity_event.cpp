#include "event/entity_event.h"

namespace cmulate
{

EntityEvent::EntityEvent(Type t) :
  type_{t}
{
}

Event::EventId EntityEvent::id() const
{
  return static_cast<EventId>(type_);
}

} // namespace

