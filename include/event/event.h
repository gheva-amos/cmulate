#ifndef CMULATE_EVENT_H__
#define CMULATE_EVENT_H__
#include <functional>
#include <cstddef>
#include <unordered_set>
#include <memory>
#include <vector>
#include "event/functor.h"
#include "event/event_vector.h"

namespace cmulate
{

class Event
{
public:
  using EventReference = std::reference_wrapper<Event>;
  using FuncReference = std::reference_wrapper<EventFunctor>;
  using ListnerSet = std::unordered_set<FuncReference, FunctorHasher, FunctorCompare>;
  using EventId = size_t;
  virtual ~Event() = default;
  void add_listener(EventFunctor& f);

  void notify();
  virtual EventId id() const = 0;

  void push_args(std::vector<std::any>& args);
protected:
  ListnerSet::iterator begin();
  ListnerSet::iterator end();
private:
  ListnerSet listeners_;
  std::vector<size_t> entity_args_;
  EventVector events_;
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
