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

} // namespace

