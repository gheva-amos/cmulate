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
    for (auto args : events_)
    {
      listener.get()(args);
    }
  }
  events_.clear();
}

Event::ListnerSet::iterator Event::begin()
{
  return listeners_.begin();
}

Event::ListnerSet::iterator Event::end()
{
  return listeners_.end();
}

void Event::push_args(std::vector<std::any>& args)
{
  events_.push_back(args);
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

