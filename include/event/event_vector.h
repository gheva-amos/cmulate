#ifndef CMULATE_EVENT_VECTOR_H__
#define CMULATE_EVENT_VECTOR_H__

#include <vector>
#include <any>
#include <mutex>

namespace cmulate
{

class EventVector
{
public:
  void add_event(std::vector<std::any>& event);
  std::vector<std::vector<std::any>> front();
private:
  std::vector<std::vector<std::any>> events_;
  std::mutex lock_;
};

} // namespace

#endif // CMULATE_EVENT_VECTOR_H__
