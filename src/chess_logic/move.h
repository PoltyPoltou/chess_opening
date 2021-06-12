#pragma once
#include "piece.h"

#include <string>
#include <tuple>
namespace chess {
class Move {
private:
  std::string uci;
  std::pair<int, int> start;
  std::pair<int, int> end;
  Piece promotion;
  bool is_promote;

public:
  Move(std::string uci);
  Move(int startRow,
       int startCol,
       int endRow,
       int endCol,
       bool is_promote = false,
       Piece promote = KING);
  std::string getUci() const;
  bool is_promotion() const;
  std::pair<int, int> getStart() const;
  std::pair<int, int> getEnd() const;
  Piece getPromotion() const;
};

} // namespace chess
