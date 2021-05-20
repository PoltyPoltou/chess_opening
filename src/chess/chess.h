#pragma once
#include <cstdint>
#include <iostream>
#include <tuple>
namespace chess
{

    /*
    square is to index every square on the chess board order is : A1 = 0, A2, ... , H8 = 63
    For that we use enum Column, Row are integers
    The sum gives the square ex Column::A + 1 returns 0 and Column::H + 8  returns 63
    */
    enum class Column
    {
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H
    };
    int operator+(const Column &c, const int &r);
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
    enum Piece
    {
        ROOK = 'r',
        KNIGHT = 'n',
        BISHOP = 'b',
        KING = 'k',
        QUEEN = 'q',
        PAWN = 'p'
    };
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
    };
    std::ostream &operator<<(std::ostream &os, BoardState &brdState);

} // namespace chess