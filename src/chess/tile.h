#pragma once

#include "piece.h"

namespace chess
{

    class Tile
    {
    private:
        enum Piece p;
        bool white;
        bool empty;

    public:
        bool is_empty() const;
        bool color() const;
        char value() const;
        enum Piece piece() const;
        Tile(enum Piece piece, bool white);
        Tile();
    };
}