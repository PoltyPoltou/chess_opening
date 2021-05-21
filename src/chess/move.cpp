#include "move.h"
namespace chess
{

    Move::Move(std::string uci) : uci(uci),
                                  start(std::make_tuple(uci[1] - '0', uci[0] - 'a')),
                                  end(std::make_tuple(uci[3] - '0', uci[2] - 'a')) {}

    Move::Move(int startRow, int startCol, int endRow, int endCol)
        : start(std::make_tuple(startRow, startCol)),
          end(std::make_tuple(endRow, endCol))
    {
        char arr[]{startCol + 'a',
                   startRow + '0',
                   endCol + 'a',
                   endRow + '0'};
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

} // namespace chess