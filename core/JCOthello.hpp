#include "OthelloAI.hpp"
#include <vector>
#include <algorithm>
#include <iostream>
namespace jaredac1
{
    class JCOthello: public OthelloAI
    {
        public:
        JCOthello();
        ~JCOthello();
        std::pair<int, int> chooseMove(const OthelloGameState& state);
        std::vector<std::pair<int,int>> findMoves(const OthelloGameState& state);
        int search(OthelloGameState& state, int d, int myturn);
        int calculate(const OthelloGameState& state);

     };
}
