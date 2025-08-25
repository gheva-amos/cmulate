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
  using EventReference = std::reference_wrapper<Event>;
  using EventId = size_t;
  virtual ~Event() = default;
  void add_listener(EventFunctor& f);

  void notify();
  virtual EventId id() const = 0;
private:
  std::unordered_set<std::reference_wrapper<EventFunctor>, FunctorHasher, FunctorCompare> listeners_;
};

struct EventCompare
{
  bool operator()(Event::EventReference a, Event::EventReference b) const noexcept;
};

struct EventHash
{
  std::size_t operator()(Event::EventReference r) const noexcept;
};

} // namespace

#endif // CMULATE_EVENT_H__
