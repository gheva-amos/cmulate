#include "tile.h"

namespace cmulate
{

Tile::Tile(Type type, bool can_walk_through) :
  type_{type}, can_walk_through_{can_walk_through}
{
}

bool Tile::can_walk_through() const
{
  return can_walk_through_;
}

bool& Tile::can_walk_through()
{
  return can_walk_through_;
}

Tile::Type Tile::type() const
{
  return type_;
}

Tile::Type& Tile::type()
{
  return type_;
}

} // namespace

