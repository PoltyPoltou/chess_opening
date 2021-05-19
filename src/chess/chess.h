#pragma once
#include <cstdint>
#include <iostream>
#include <tuple>
namespace chess
{

    /*
    square is to index every square on the chess board order is : A1 = 0, A2, ... , H8 = 63
    */
    typedef uint8_t square;

    /*
    piece is to index pieces :
        0 empty
        1 Rook
        2 Knight
        3 Bishop
        4 King
        5 Queen
        6 Pawn
        Positive for white, negative for black
    */
    typedef int8_t piece;

    /*
        Standard board for chess
    */
    const piece STD_BOARD[8][8] = {{1, 2, 3, 4, 5, 3, 2, 1},
                                   {6, 6, 6, 6, 6, 6, 6, 6},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 0, 0, 0, 0, 0, 0, 0},
                                   {-6, -6, -6, -6, -6, -6, -6, -6},
                                   {-1, -2, -3, -4, -5, -3, -2, -1}};
    struct coords
    {
        uint8_t col, row;
    };
    /*
    Defines the state of a chess board
    */
    class BoardState
    {
    private:
        piece board[8][8];

    public:
        BoardState();
        ~BoardState();
        const piece *operator[](int i) const;
    };
    std::ostream &operator<<(const std::ostream &os, const BoardState &brdState);

} // namespace chess