#include "move.h"
namespace chess
{

    Move::Move(std::string uci) : uci(uci),
                                  start(std::make_pair(uci[1] - '1', uci[0] - 'a')),
                                  end(std::make_pair(uci[3] - '1', uci[2] - 'a'))
    {
        if (uci.length() == 5)
        {
            char prom = uci[4];
            switch (prom)
            {
            case 'q':
                promotion = QUEEN;
                break;
            case 'b':
                promotion = BISHOP;
                break;
            case 'n':
                promotion = KNIGHT;
                break;
            case 'r':
                promotion = ROOK;
                break;
            default:
                promotion = KING; // so that any promotion of this type will eventually fail
                break;
            }
        }
        else
        {
            promotion = KING; // so that any promotion of this type will eventually fail
        }
    }

    Move::Move(int startRow, int startCol, int endRow, int endCol, Piece promote)
        : start(std::make_pair(startRow, startCol)),
          end(std::make_pair(endRow, endCol)),
          promotion(promote)
    {
        char arr[]{startCol + 'a',
                   startRow + '1',
                   endCol + 'a',
                   endRow + '1',
                   promote};
        uci = std::string(arr);
    }

    std::string Move::getUci() const
    {
        return uci;
    }

    std::pair<int, int> Move::getStart() const
    {
        return start;
    }

    std::pair<int, int> Move::getEnd() const
    {
        return end;
    }
    Piece Move::getPromotion() const
    {
        return promotion;
    }

} // namespace chess