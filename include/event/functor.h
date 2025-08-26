#ifndef CMULATE_FUNCTOR_H__
#define CMULATE_FUNCTOR_H__

#include <cstddef>
#include <string>
#include <functional>
#include <memory>
#include <any>
#include <vector>

namespace cmulate
{

class EntityManager;
class Functor
{
public:
  using Function = std::reference_wrapper<Functor>;
  virtual ~Functor() = default;
  virtual std::string hash_seed() const;
  virtual size_t hash() const;
  bool operator==(const Function other) const noexcept;
};

struct FunctorCompare
{
  bool operator()(Functor::Function a, Functor::Function b) const noexcept;
};

struct FunctorHasher
{
  size_t operator()(Functor::Function const& f) const noexcept;
};

class EventFunctor : public Functor
{
public:
  virtual void operator()(std::vector<std::any>& args) = 0;
  virtual std::string hash_seed() const override;
};

} // namespace

#endif // CMULATE_FUNCTOR_H__
