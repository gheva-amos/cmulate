#ifndef CMULATE_TRIGGER_H__
#define CMULATE_TRIGGER_H__

#include "event/functor.h"
#include <functional>
#include <unordered_set>

namespace cmulate
{

class Trigger
{
public:
  virtual ~Trigger() = default;
  void add_function(Functor& func);
  void trigger();
protected:
  virtual void do_trigger(Functor& func) = 0;
  std::unordered_set<Functor::Function, FunctorHasher, FunctorCompare> functions_;
};

} // namespace

#endif // CMULATE_TRIGGER_H__
