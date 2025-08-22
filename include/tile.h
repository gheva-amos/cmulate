#ifndef CMULATE_TILE_H__
#define CMULATE_TILE_H__

namespace cmulate
{

class Tile
{
public:
  enum class Type
  {
    grass,
    water,
    mountain,
    unknown
  };
  Tile() = default;
  Tile(Type type, bool can_walk_through);
  bool can_walk_through() const;
  bool& can_walk_through();
  Type type() const;
  Type& type();
private:
  Type type_{Type::unknown};
  bool can_walk_through_{false};
};

} // namespace

#endif // CMULATE_TILE_H__
