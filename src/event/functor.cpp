#include "event/functor.h"

namespace cmulate
{
std::string Functor::hash_seed() const
{
  return "functor";
}

size_t Functor::hash() const
{
  return std::hash<std::string>{}(hash_seed());
}

bool Functor::operator==(const Function other) const noexcept
{
  return hash_seed() == other.get().hash_seed();
}

std::string EventFunctor::hash_seed() const
{
  return "Event Functor";
}

bool FunctorCompare::operator()(
    Functor::Function a, Functor::Function b) const noexcept
{
  return a.get() == b;
}

size_t FunctorHasher::operator()(Functor::Function const& f) const noexcept
{
  return f.get().hash();
}

} // namespace

