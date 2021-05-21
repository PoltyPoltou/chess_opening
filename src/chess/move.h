#pragma once
#include <tuple>
namespace chess
{
    class Move
    {
    private:
        std::string uci;
        std::tuple<int, int> start;
        std::tuple<int, int> end;

    public:
        Move(std::string uci);
        Move(int startRow, int startCol, int endRow, int endCol);
        std::string getUci() const;
        std::tuple<int, int> getStart() const;
        std::tuple<int, int> getEnd() const;
    };

} // namespace chess
