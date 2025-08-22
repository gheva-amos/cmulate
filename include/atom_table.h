#ifndef CMULATE_ATOM_TABLE_H__
#define CMULATE_ATOM_TABLE_H__

#include <unordered_map>
#include <vector>
#include <string>

namespace cmulate
{

class AtomTable
{
public:
  using Atom = size_t;
  Atom intern(const std::string& atom);
  const std::string& value(Atom atom);
private:
  std::unordered_map<std::string, Atom> s_to_i_;
  std::vector<std::string> i_to_s_;
};

} // namespace
#endif // CMULATE_ATOM_TABLE_H__
