#include "chess.h"
namespace chess
{

    BoardState::BoardState()
    {
        for (int i = 0; i < 8; i++)
        {
            std::copy(STD_BOARD[i], STD_BOARD[i] + 8, board[i]);
        }
    }

    BoardState::~BoardState()
    {
    }
    const piece *BoardState::operator[](int i) const
    {
        return board[i];
    }

    std::ostream &
    operator<<(std::ostream &os, const BoardState &brdState)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                os << std::to_string(brdState[i][j]);
            }
            os << std::endl;
        }
        return os;
    }
}
