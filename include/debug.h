#ifndef CMULATE_DEBUG_H__
#define CMULATE_DEBUG_H__

#include <ostream>
#include <iostream>
#include <string>
#include <sstream>

namespace cmulate
{

#ifdef DEBUG
class DebugPrinter
{
public:
  DebugPrinter() : out{std::cout} {}
  std::ostream& operator<<(const std::string& str)
  {
    return out << str;
  }
private:
  std::ostream& out;
};
#else
class DebugPrinter // For production NOOP
{
public:
  DebugPrinter() {}
  std::ostream& operator<<(const std::string& str)
  {
    out.clear();
    return out;
  }
private:
  std::stringstream out;
};
#endif
} // namespace

#define DBG_MSG(message) (DebugPrinter() << __FILE__ << ':' << __LINE__ << message)
#endif // CMULATE_DEBUG_H__
