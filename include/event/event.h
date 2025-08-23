#ifndef CMULATE_EVENT_H__
#define CMULATE_EVENT_H__
#include <functional>
#include <cstddef>
#include <unordered_set>
#include <memory>
#include "event/functor.h"

namespace cmulate
{

class Event
{
public:
  using EventId = size_t;
  virtual ~Event() = default;
  void add_listener(EventFunctor& f);

  void notify();
  virtual EventId id() const = 0;
private:
  std::unordered_set<std::reference_wrapper<EventFunctor>, FunctorHasher, FunctorCompare> listeners_;
};

} // namespace

#endif // CMULATE_EVENT_H__
