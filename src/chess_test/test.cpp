#include "boardstate.h"
#include <gtest/gtest.h>

void testMove(chess::BoardState &state, std::string coords1, std::string coords2, chess::Piece p, bool colour)
{
    chess::Move mv(coords1 + coords2);
    ASSERT_TRUE(state.isLegal(mv));
    EXPECT_NO_THROW(state.playMove(mv));
    EXPECT_EQ(*state.get(coords1), chess::Tile());
    EXPECT_EQ(*state.get(coords2), chess::Tile(p, colour));
}

TEST(BasicMoves, Pawn)
{
    chess::BoardState state;
    testMove(state, "e2", "e3", chess::PAWN, chess::WHITE);
}

TEST(BasicMoves, Knight)
{
    chess::BoardState state;
    testMove(state, "g1", "f3", chess::KNIGHT, chess::WHITE);
}

TEST(BasicMoves, King)
{
    chess::BoardState state;
    state.playMove(chess::Move("e2e3"));
    state.playMove(chess::Move("e7e6"));
    testMove(state, "e1", "e2", chess::KING, chess::WHITE);
}

TEST(BasicMoves, Bishop)
{
    chess::BoardState state;
    state.playMove(chess::Move("e2e3"));
    state.playMove(chess::Move("e7e6"));
    testMove(state, "f1", "d3", chess::BISHOP, chess::WHITE);
}

TEST(BasicMoves, Rook)
{
    chess::BoardState state;
    state.playMove(chess::Move("g1f3"));
    state.playMove(chess::Move("e7e6"));
    state.playMove(chess::Move("e2e3"));
    state.playMove(chess::Move("d7d6"));
    state.playMove(chess::Move("f1d3"));
    state.playMove(chess::Move("a7a6"));
    testMove(state, "h1", "f1", chess::ROOK, chess::WHITE);
}

TEST(BasicMoves, Queen)
{
    //diagonal
    chess::BoardState state;
    state.playMove(chess::Move("e2e3"));
    state.playMove(chess::Move("e7e6"));
    testMove(state, "d1", "f3", chess::QUEEN, chess::WHITE);

    //Rook
    state = chess::BoardState();
    state.playMove(chess::Move("e2e3"));
    state.playMove(chess::Move("e7e6"));
    state.playMove(chess::Move("e1e2"));
    state.playMove(chess::Move("d7d6"));
    testMove(state, "d1", "e1", chess::QUEEN, chess::WHITE);
}

TEST(Castle, Long)
{
    chess::BoardState state;
    state.emptyTile(state.get("b1"));
    state.emptyTile(state.get("c1"));
    state.emptyTile(state.get("d1"));
    testMove(state, "e1", "c1", chess::KING, chess::WHITE);
    EXPECT_EQ(*state.get("d1"), chess::Tile(chess::ROOK, chess::WHITE));
    EXPECT_TRUE(state.get("a1")->is_empty());
}

TEST(Castle, Short)
{
    chess::BoardState state;
    state.emptyTile(state.get("f1"));
    state.emptyTile(state.get("g1"));
    testMove(state, "e1", "g1", chess::KING, chess::WHITE);
    EXPECT_EQ(*state.get("f1"), chess::Tile(chess::ROOK, chess::WHITE));
    EXPECT_TRUE(state.get("h1")->is_empty());
}

TEST(Castle, DisableKing)
{
    chess::BoardState state;
    state.emptyTile(state.get("b1"));
    state.emptyTile(state.get("c1"));
    state.emptyTile(state.get("d1"));
    state.emptyTile(state.get("f1"));
    state.emptyTile(state.get("g1"));
    state.emptyTile(state.get("e2"));
    state.playMove(chess::Move("e1e2"));
    state.playMove(chess::Move("e7e6"));
    state.playMove(chess::Move("e2e1"));
    state.playMove(chess::Move("d7d6"));
    EXPECT_FALSE(state.isLegal(chess::Move("e1g1")));
    EXPECT_FALSE(state.isLegal(chess::Move("e1c1")));
}

TEST(Castle, DisableRookShort)
{
    chess::BoardState state;
    state.emptyTile(state.get("b1"));
    state.emptyTile(state.get("c1"));
    state.emptyTile(state.get("d1"));
    state.emptyTile(state.get("f1"));
    state.emptyTile(state.get("g1"));
    state.emptyTile(state.get("e2"));
    state.playMove(chess::Move("h1g1"));
    state.playMove(chess::Move("e7e6"));
    state.playMove(chess::Move("g1h1"));
    state.playMove(chess::Move("d7d6"));
    EXPECT_FALSE(state.isLegal(chess::Move("e1g1")));
    EXPECT_TRUE(state.isLegal(chess::Move("e1c1")));
}

TEST(Castle, DisableRookLong)
{
    chess::BoardState state;
    state.emptyTile(state.get("b1"));
    state.emptyTile(state.get("c1"));
    state.emptyTile(state.get("d1"));
    state.emptyTile(state.get("f1"));
    state.emptyTile(state.get("g1"));
    state.emptyTile(state.get("e2"));
    state.playMove(chess::Move("a1b1"));
    state.playMove(chess::Move("e7e6"));
    state.playMove(chess::Move("b1a1"));
    state.playMove(chess::Move("d7d6"));
    EXPECT_FALSE(state.isLegal(chess::Move("e1c1")));
    EXPECT_TRUE(state.isLegal(chess::Move("e1g1")));
}
