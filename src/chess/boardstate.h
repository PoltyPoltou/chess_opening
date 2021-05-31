#pragma once
#include "move.h"
#include "tile.h"
#include <iostream>

namespace chess
{
    static const bool WHITE = true, BLACK = false;
    /*
    Defines the state of a chess board
    */
    class BoardState
    {
    private:
        Tile board[8][8];
        bool castlingRight_short[2];
        bool castlingRight_long[2];
        bool turn;
        /**
         * coords of the empty tile the pawn skipped on row 3 or 6
        */
        std::tuple<int, int> priseEnPassant;
        std::tuple<int, int> findKing(bool colour);
        Tile safeGet(int row, int col);
        bool piecePresence(int row, int col, Piece p, bool colour);

    public:
        BoardState();

        Tile *get(int row, int col);
        Tile *get(std::string str);
        Tile *get(std::tuple<int, int> coords);
        bool getTurn();

        void swapTiles(Tile *t1, Tile *t2);
        void emptyTile(Tile *t);

        bool canShortCastle(bool colour);
        bool canLongCastle(bool colour);
        bool isCheck();
        bool isAttacked(std::tuple<int, int> coords, bool colour);
        bool isLegal(Move &mv);
        bool legalPath(Piece p, bool clr, const std::tuple<int, int> &t1, const std::tuple<int, int> &t2, bool attacking = false);
        std::string playMove(Move &mv);
    };
    std::ostream &operator<<(std::ostream &os, BoardState &brdState);

} // namespace chess