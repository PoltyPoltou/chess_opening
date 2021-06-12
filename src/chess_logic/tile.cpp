#include "tile.h"

#include <cctype>
namespace chess {

bool Tile::is_empty() const {
  return empty;
}
bool Tile::color() const {
  return white;
}
char Tile::value() const {
  if (empty)
    return '-';
  else
    return white ? std::toupper(static_cast<char>(p)) :
                   std::tolower(static_cast<char>(p));
}
enum Piece Tile::piece() const {
  return p;
}
Tile::Tile(Piece piece, bool white) : p(piece), white(white), empty(false) {};
Tile::Tile() : empty(true) {};

bool operator==(chess::Tile const &t1, chess::Tile const &t2) {
  if (!t1.is_empty() && !t2.is_empty()) {
    return t1.color() == t2.color() && t1.piece() == t2.piece();
  } else {
    return t1.is_empty() && t2.is_empty();
  }
}

} // namespace chess