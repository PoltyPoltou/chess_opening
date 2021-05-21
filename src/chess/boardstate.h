#pragma once
#include "move.h"
#include "tile.h"
#include <iostream>

namespace chess
{
    /*
    Defines the state of a chess board
    */
    class BoardState
    {
    private:
        Tile board[8][8];

    public:
        BoardState();
        ~BoardState();
        Tile *get(int i, int j);
        void playMove(Move mv);
        bool isLegal(Move mv);
    };
    std::ostream &operator<<(std::ostream &os, BoardState &brdState);

} // namespace chess