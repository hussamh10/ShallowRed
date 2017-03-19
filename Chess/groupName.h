#ifndef GROUPNAME_H
#define GROUPNAME_H

#include "player.h"
#include <list>


class playerGROUP_NAME : public chessPlayer
{
    public:
		std::list<chessState> getStates() { return states; }
        playerGROUP_NAME(int playerColor);
        int decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth=1);
		void gameResult(int winner);
    protected:

    private:
		std::list<chessState> states;
};

#endif // GROUPNAME_H
