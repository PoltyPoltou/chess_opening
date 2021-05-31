#pragma once
#include "piece.h"
#include <tuple>
namespace chess
{
    class Move
    {
    private:
        std::string uci;
        std::tuple<int, int> start;
        std::tuple<int, int> end;
        Piece promotion;

    public:
        Move(std::string uci);
        Move(int startRow, int startCol, int endRow, int endCol, Piece promote);
        std::string getUci() const;
        std::tuple<int, int> getStart() const;
        std::tuple<int, int> getEnd() const;
        Piece getPromotion() const;
    };

} // namespace chess
