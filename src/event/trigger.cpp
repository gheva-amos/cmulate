#include "event/trigger.h"
#include "debug.h"
namespace cmulate
{

void Trigger::add_function(Functor& func)
{
  DBG_MSG("adding a functor") << std::endl;
  functions_.insert(func);
}

void Trigger::trigger()
{
  DBG_MSG("triggering functors") << std::endl;
  for (auto func : functions_)
  {
    do_trigger(func.get());
  }
}

} // namespace

