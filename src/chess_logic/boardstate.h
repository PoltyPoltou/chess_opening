#pragma once
#include "move.h"
#include "tile.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
namespace chess
{
    static const bool WHITE = true, BLACK = false;
    /*
    Defines the state of a chess board
    */
    class BoardState
    {
        typedef std::pair<Piece, bool> coloredPiece;
        typedef std::unordered_set<Tile const *> TileSet;

    private:
        Tile board[8][8];
        std::unordered_map<Piece, TileSet> piece_map;
        bool castlingRight_short[2];
        bool castlingRight_long[2];
        bool turn;
        /**
         * coords of the empty tile the pawn skipped on row 3 or 6
        */
        std::pair<int, int> priseEnPassant;
        std::pair<int, int> findKing(bool colour);
        Tile safeGet(int row, int col);
        bool piecePresence(int row, int col, Piece p, bool colour);

    public:
        BoardState();

        Tile *get(int row, int col);
        Tile *get(std::string str);
        Tile *get(std::pair<int, int> coords);
        bool getTurn();

        void swapTiles(Tile *t1, Tile *t2);
        void emptyTile(Tile *t);
        void setTile(Tile *emplacement, Tile const &new_tile);

        bool canShortCastle(bool colour);
        bool canLongCastle(bool colour);
        bool isCheck();
        bool isAttacked(std::pair<int, int> coords, bool colour);
        bool isLegal(Move const &mv);
        bool legalPath(Piece p, bool clr, const std::pair<int, int> &t1, const std::pair<int, int> &t2, bool attacking = false);
        std::string playMove(Move const &mv);
    };
    std::ostream &operator<<(std::ostream &os, BoardState &brdState);

} // namespace chess