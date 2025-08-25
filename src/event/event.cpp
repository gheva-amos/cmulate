#include "event/event.h"
#include "debug.h"

namespace cmulate
{

void Event::add_listener(EventFunctor& f)
{
  listeners_.insert(f);
}

void Event::notify()
{
  for (auto listener : listeners_)
  {
    listener.get()(id());
  }
}

std::size_t EventHash::operator()(Event::EventReference r) const noexcept
{
  return std::hash<Event::EventId>{}(r.get().id());
}

bool EventCompare::operator()(Event::EventReference a, Event::EventReference b) const noexcept
{
  return a.get().id() == b.get().id();
}

} // namespace

