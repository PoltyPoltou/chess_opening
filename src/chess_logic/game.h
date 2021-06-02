#pragma once
#include "boardstate.h"
#include <map>
#include <vector>
namespace chess
{
    class Game
    {
    private:
        int moveStartNumber;
        std::vector<BoardState> mainline;
        std::map<BoardState, std::vector<Game>> variations;
        std::map<BoardState, std::string> algebricNotations;
        std::map<BoardState, std::string> comments;

    public:
        Game();
        Game(std::string pathToPgn);
        ~Game();
    };

} // namespace chess
