#include "move.h"
namespace chess
{

    Move::Move(std::string uci, Piece promote) : uci(uci),
                                                 start(std::make_tuple(uci[1] - '1', uci[0] - 'a')),
                                                 end(std::make_tuple(uci[3] - '1', uci[2] - 'a')),
                                                 promotion(promote) {}

    Move::Move(int startRow, int startCol, int endRow, int endCol, Piece promote)
        : start(std::make_tuple(startRow, startCol)),
          end(std::make_tuple(endRow, endCol)),
          promotion(promote)
    {
        char arr[]{startCol + 'a',
                   startRow + '1',
                   endCol + 'a',
                   endRow + '1'};
        uci = std::string(arr);
    }

    std::string Move::getUci() const
    {
        return uci;
    }

    std::tuple<int, int> Move::getStart() const
    {
        return start;
    }

    std::tuple<int, int> Move::getEnd() const
    {
        return end;
    }
    Piece Move::getPromotion() const
    {
        return promotion;
    }

} // namespace chess