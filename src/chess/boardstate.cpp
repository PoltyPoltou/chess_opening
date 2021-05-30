#include "boardstate.h"
namespace chess
{
    /*
        Standard board for chess
    */
    static const Tile STD_BOARD[8][8] = {
        {Tile(ROOK, true), Tile(KNIGHT, true), Tile(BISHOP, true), Tile(QUEEN, true), Tile(KING, true), Tile(BISHOP, true), Tile(KNIGHT, true), Tile(ROOK, true)},
        {Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true)},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false)},
        {Tile(ROOK, false), Tile(KNIGHT, false), Tile(BISHOP, false), Tile(QUEEN, false), Tile(KING, false), Tile(BISHOP, false), Tile(KNIGHT, false), Tile(ROOK, false)}};

    BoardState::BoardState()
    {
        for (int i = 0; i < 8; i++)
        {
            std::copy(STD_BOARD[i], STD_BOARD[i] + 8, board[i]);
        }
    }

    BoardState::~BoardState() {}

    Tile *BoardState::get(int row, int col)
    {
        return &board[row][col];
    }

    std::ostream &
    operator<<(std::ostream &os, BoardState &brdState)
    {
        for (int j = 0; j < 8; j++)
        {
            for (int i = 0; i < 8; i++)
            {
                os << brdState.get(7 - j, i)->value();
            }
            os << std::endl;
        }
        return os;
    }

}
