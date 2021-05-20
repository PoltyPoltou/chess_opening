#include "chess.h"
namespace chess
{
    /*
        Standard board for chess
    */
    static const Tile STD_BOARD[8][8] = {
        {Tile(ROOK, true), Tile(KNIGHT, true), Tile(BISHOP, true), Tile(KING, true), Tile(QUEEN, true), Tile(BISHOP, true), Tile(KNIGHT, true), Tile(ROOK, true)},
        {Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true), Tile(PAWN, true)},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile(), Tile()},
        {Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false), Tile(PAWN, false)},
        {Tile(ROOK, false), Tile(KNIGHT, false), Tile(BISHOP, false), Tile(KING, false), Tile(QUEEN, false), Tile(BISHOP, false), Tile(KNIGHT, false), Tile(ROOK, false)}};

    BoardState::BoardState()
    {
        for (int i = 0; i < 8; i++)
        {
            std::copy(STD_BOARD[i], STD_BOARD[i] + 8, board[i]);
        }
    }

    BoardState::~BoardState() {}

    Tile *BoardState::get(int i, int j)
    {
        return &board[i][j];
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

    int operator+(Column c, int r)
    {
        return static_cast<int>(c) * 8 + r - 1;
    }

    bool Tile::is_empty() const
    {
        return empty;
    }
    bool Tile::color() const
    {
        return white;
    }
    char Tile::value() const
    {
        if (empty)
            return '-';
        else
            return white ? std::toupper(static_cast<char>(p)) : std::tolower(static_cast<char>(p));
    }
    enum Piece Tile::piece() const
    {
        return p;
    }
    Tile::Tile(Piece piece, bool white) : p(piece), white(white), empty(false){};
    Tile::Tile() : empty(true){};

}
