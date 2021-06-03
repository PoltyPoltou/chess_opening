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
        turn = WHITE;
        castlingRight_short[WHITE] = true;
        castlingRight_short[BLACK] = true;
        castlingRight_long[WHITE] = true;
        castlingRight_long[BLACK] = true;
        for (int i = 0; i < 8; i++)
        {
            std::copy(STD_BOARD[i], STD_BOARD[i] + 8, board[i]);
        }
    }

    /*
        Row and col index start at 0
    */
    Tile *BoardState::get(int row, int col)
    {
        return &board[row][col];
    }

    /*
        get the coord given a string representing a tile : e5, a1 ...
    */
    Tile *BoardState::get(std::string str)
    {
        return get(str[1] - '1', str[0] - 'a');
    }

    Tile *BoardState::get(std::tuple<int, int> coords)
    {
        return &board[std::get<0>(coords)][std::get<1>(coords)];
    }

    Tile BoardState::safeGet(int row, int col)
    {
        if (row >= 0 && row < 8 && col >= 0 && col < 8)
            return board[row][col];
        else
            return Tile();
    }

    bool BoardState::getTurn()
    {
        return turn;
    }

    void BoardState::swapTiles(Tile *t1, Tile *t2)
    {
        std::swap(*t1, *t2);
    }

    void BoardState::emptyTile(Tile *t)
    {
        if (!t->is_empty())
        {
            *t = std::move(Tile());
        }
    }

    /*
        Does not check for move validity, call isLegal(mv) first
        Undefined behavior if the move is not legal
    */
    std::string BoardState::playMove(Move &mv)
    {
        Tile *played = get(mv.getStart());
        int r1 = std::get<0>(mv.getStart()), c1 = std::get<1>(mv.getStart());
        int r2 = std::get<0>(mv.getEnd()), c2 = std::get<1>(mv.getEnd());
        std::string uci = mv.getUci();
        // Check if the move is a castle move,
        // we set to false the given castling right
        // And we only move the rook
        if (played->piece() == Piece::KING && (uci == "e1c1" || uci == "e1g1" || uci == "e8c8" || uci == "e8g8"))
        {
            if (played->color() == WHITE)
            {
                castlingRight_short[WHITE] = false;
                castlingRight_long[WHITE] = false;
                if (uci == "e1g1")
                {
                    swapTiles(get("h1"), get("f1"));
                }
                else
                {
                    swapTiles(get("a1"), get("d1"));
                }
            }
            else
            {
                castlingRight_short[BLACK] = false;
                castlingRight_long[BLACK] = false;
                if (uci == "e8g8")
                {
                    swapTiles(get("h8"), get("f8"));
                }
                else
                {
                    swapTiles(get("a8"), get("d8"));
                }
            }
        }
        // remove castling right if needed
        if (uci.substr(0, 2) == "a1" || uci.substr(0, 2) == "a8")
        {
            castlingRight_long[turn] = false;
        }
        if (uci.substr(0, 2) == "h1" || uci.substr(0, 2) == "h8")
        {
            castlingRight_short[turn] = false;
        }
        if (uci.substr(0, 2) == "e1" || uci.substr(0, 2) == "e8")
        {
            castlingRight_short[turn] = false;
            castlingRight_long[turn] = false;
        }

        if (played->piece() == PAWN && ((uci[1] == '2' && uci[3] == '4') || (uci[1] == '7' && uci[3] == '5')))
        {
            //set the prise en passant tile
            priseEnPassant = std::make_tuple((r1 + r2) / 2, c1);
        }
        else
        {
            //reset it otherwise
            priseEnPassant = std::make_tuple(-1, -1);
        }

        // we have to check if it is en passant, to remove the captured pawn
        if (played->piece() == PAWN && priseEnPassant == mv.getEnd())
        {
            emptyTile(get(std::make_tuple(r1, c2)));
        }
        //promotion
        if (played->piece() == PAWN && (uci[3] == '8' || uci[3] == '1'))
        {
            *played = Tile(mv.getPromotion(), turn);
        }
        // Now we move the piece
        swapTiles(get(mv.getStart()), get(mv.getEnd()));
        emptyTile(get(mv.getStart()));
        //swap the turn color
        turn = !turn;
    }

    /**
        \brief Check if the piece p of colour clr at coords t1 can go to coords t2 with a legal movement
        Does not handle castling
        \param attacking checks if the tile is attacked (ie it will not check anything about t2)
    */
    bool BoardState::legalPath(Piece p, bool clr, const std::tuple<int, int> &t1, const std::tuple<int, int> &t2, bool attacking)
    {
        int r1 = std::get<0>(t1), c1 = std::get<1>(t1);
        int r2 = std::get<0>(t2), c2 = std::get<1>(t2);
        if (!get(t2)->is_empty() && get(t2)->color() == clr && !attacking)
        {
            return false;
        }
        switch (p)
        {
        case ROOK:
        {
            if (r1 == r2)
            {
                for (int c = std::min(c1, c2) + 1; c < std::max(c1, c2); c++)
                {
                    if (!get(r1, c)->is_empty())
                    {
                        return false;
                    }
                }
                return true;
            }
            else if (c1 == c2)
            {
                for (int r = std::min(r1, r2) + 1; r < std::max(r1, r2); r++)
                {
                    if (!get(r, c1)->is_empty())
                    {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        break;

        case BISHOP:
        {
            if (r1 + c1 == r2 + c2 || r1 - c1 == r2 - c2)
            {
                int rDir = (r2 - r1) / abs(r2 - r1), cDir = (c2 - c1) / abs(c2 - c1);
                int r = r1 + rDir, c = c1 + cDir;
                while (r != r2 && c != c2) // both condition should go off at the same time
                {
                    if (!get(r, c)->is_empty())
                    {
                        return false;
                    }
                    r += rDir;
                    c += cDir;
                }
                return true;
            }
            return false;
        }
        break;

        case KNIGHT:
            return abs(r1 - r2) + abs(c1 - c2) == 3 && r1 != r2 && c1 != c2; // circle of radius 3 but can't be on a liine
            break;

        case QUEEN:
            if (r1 + c1 == r2 + c2 || r1 - c1 == r2 - c2)
            {
                return legalPath(BISHOP, clr, t1, t2);
            }
            else
            {
                return legalPath(ROOK, clr, t1, t2);
            }
            break;

        case PAWN:
        {
            bool stdMove, takingMove;
            //first push of a pawn can be for two tiles if the middle tile is empty
            bool firstPush = c1 == c2 &&
                             ((clr == WHITE && r1 == 1 && r2 == 3 && get(2, c1)->is_empty()) ||
                              (clr == BLACK && r1 == 6 && r2 == 4 && get(5, c1)->is_empty()));
            if (r2 - r1 == (clr == WHITE) - (clr == BLACK))
            {
                stdMove = c1 == c2;
                takingMove = !stdMove && abs(c1 - c2) == (!get(t2)->is_empty() && get(t2)->color() != clr);
            }
            if (!attacking)
            {
                return takingMove || (get(t2)->is_empty() && (stdMove || firstPush));
            }
            else
            {
                return (r2 - r1 == (clr == WHITE) - (clr == BLACK)) && abs(c1 - c2) == 1;
            }
        }
        break;

        case KING:
            return abs(r1 - r2) <= 1 && abs(c1 - c2) <= 1;
            break;
        }
        return false;
    }

    /**
        \brief Finds the king of the given colour, and return its coordinates.
        If there is not king, it will return the -1,-1 coords
    */
    std::tuple<int, int> BoardState::findKing(bool colour)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (get(i, j)->piece() == KING && get(i, j)->color() == colour)
                {
                    return std::make_tuple(i, j);
                }
            }
        }
        std::cerr << "findKing was used on a BoardState that has no king" << std::endl;
        return std::make_tuple(-1, -1);
    }
    /**
     * \brief checks if the piece p with given colour is at the given position
     */
    bool BoardState::piecePresence(int row, int col, Piece p, bool colour)
    {
        Tile pieceTile = safeGet(row, col);
        return !pieceTile.is_empty() && pieceTile.piece() == p && pieceTile.color() == colour;
    }

    bool BoardState::isCheck()
    {
        return isAttacked(findKing(turn), !turn);
    }
    /**
     * \brief checks if the tile at coords is attacked by a piece of the given colour
    */
    bool BoardState::isAttacked(std::tuple<int, int> coords, bool colour)
    {
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                Tile *t = get(r, c);
                if (!t->is_empty() && t->color() == colour && legalPath(t->piece(), t->color(), std::make_tuple(r, c), coords, true))
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool BoardState::isLegal(Move &mv)
    {
        Tile *t1 = get(mv.getStart());
        int r1 = std::get<0>(mv.getStart()), c1 = std::get<1>(mv.getStart());
        Tile *t2 = get(mv.getEnd());
        int r2 = std::get<0>(mv.getEnd()), c2 = std::get<1>(mv.getEnd());
        // checks that the move is not absurd
        if (!t1->is_empty() && t1->color() == turn && mv.getStart() != mv.getEnd())
        {
            // We check that the piece can move from t1 to t2 without looking at checks, pin etc...
            bool movePossible = false;
            switch (t1->piece())
            {
            case PAWN:
            {
                bool standardMove, enPassant;
                standardMove = legalPath(PAWN, t1->color(), mv.getStart(), mv.getEnd());
                if (!standardMove)
                {
                    enPassant = r2 - r1 == (t1->color() == WHITE) - (t1->color() == BLACK) &&
                                abs(c1 - c2) == (mv.getEnd() == priseEnPassant);
                }
                //promotion check
                bool promotion = (r2 != 7 && r2 != 0) ||          // last row ? (no colour check as the rules won't allow the other color)
                                 (mv.getPromotion() == KNIGHT) || // checks that the promotion is valid
                                 (mv.getPromotion() == ROOK) ||
                                 (mv.getPromotion() == ROOK) ||
                                 (mv.getPromotion() == QUEEN);

                movePossible = (standardMove && promotion) || enPassant;
            }
            break;
            case KING:
            {
                bool standardMove, castleMove = false;
                standardMove = legalPath(KING, t1->color(), mv.getStart(), mv.getEnd());
                if (!standardMove)
                {
                    if (mv.getUci() == "e1c1")
                    {
                        castleMove = !isCheck() && !isAttacked(std::make_tuple(0, 3), !t1->color());
                    }
                    if (mv.getUci() == "e8c8")
                    {
                        castleMove = !isCheck() && !isAttacked(std::make_tuple(7, 3), !t1->color());
                    }
                    if (mv.getUci() == "e1g1")
                    {
                        castleMove = !isCheck() && !isAttacked(std::make_tuple(0, 5), !t1->color());
                    }
                    if (mv.getUci() == "e8g8")
                    {
                        castleMove = !isCheck() && !isAttacked(std::make_tuple(7, 5), !t1->color());
                    }
                }
                movePossible = standardMove || castleMove;
            }
            break;
            default:
                movePossible = legalPath(t1->piece(), t1->color(), mv.getStart(), mv.getEnd());
                break;
            }

            if (movePossible)
            {
                bool legalBoardState;
                Tile backupEndTile = *get(mv.getEnd());

                // First we emulate the move
                swapTiles(get(mv.getStart()), get(mv.getEnd()));
                emptyTile(get(mv.getStart()));
                // We verify that the king of playing side is not in check
                legalBoardState = !isCheck();

                // Then we revert the move
                swapTiles(get(mv.getStart()), get(mv.getEnd()));
                *get(mv.getEnd()) = std::move(backupEndTile);

                return legalBoardState;
            }
        }
        return false;
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
