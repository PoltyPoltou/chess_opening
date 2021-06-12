#include "move.h"
namespace chess {

Move::Move(std::string uci) :
    uci(uci),
    start(std::make_pair(uci[1] - '1', uci[0] - 'a')),
    end(std::make_pair(uci[3] - '1', uci[2] - 'a')) {
  if (uci.length() == 5) {
    char prom = uci[4];
    switch (prom) {
      case 'q':
        promotion = QUEEN;
        is_promote = true;
        break;
      case 'b':
        promotion = BISHOP;
        is_promote = true;
        break;
      case 'n':
        promotion = KNIGHT;
        is_promote = true;
        break;
      case 'r':
        promotion = ROOK;
        is_promote = true;
        break;
      default:
        promotion =
            KING; // so that any promotion of this type will eventually fail
        is_promote = false;
        uci = uci.substr(0, 4); // we remove the promotion part as it is false
        break;
    }
  } else {
    promotion = KING; // so that any promotion of this type will eventually fail
    is_promote = false;
  }
}

Move::Move(int startRow,
           int startCol,
           int endRow,
           int endCol,
           bool is_promote,
           Piece promote) :
    start(std::make_pair(startRow, startCol)),
    end(std::make_pair(endRow, endCol)),
    is_promote(is_promote),
    promotion(promote) {
  char arr[] {startCol + 'a', startRow + '1', endCol + 'a', endRow + '1'};
  uci = std::string(arr);

  if (is_promote) {
    uci += static_cast<char>(promote);
  }
}

std::string Move::getUci() const {
  return uci;
}

bool Move::is_promotion() const {
  return is_promote;
}

std::pair<int, int> Move::getStart() const {
  return start;
}

std::pair<int, int> Move::getEnd() const {
  return end;
}
Piece Move::getPromotion() const {
  return promotion;
}

} // namespace chess