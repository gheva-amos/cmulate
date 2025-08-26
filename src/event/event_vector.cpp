#include "event/event_vector.h"

namespace cmulate
{

void EventVector::add_event(std::vector<std::any>& event)
{
  std::lock_guard lock{lock_};
  events_.push_back(event);
}

std::vector<std::vector<std::any>> EventVector::front()
{
  std::vector<std::vector<std::any>> ret;
  {
    std::lock_guard lock{lock_};
    ret.swap(events_);
  }
  return ret;
}

} // namespace
