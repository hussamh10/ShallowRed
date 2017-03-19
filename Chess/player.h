#ifndef PLAYER_H
#define PLAYER_H
#include "move.h"
#include "chessState.h"


class chessPlayer
{
    private:
        virtual double evaluateState() { return 1;};
    public:
        chessPlayer(int playerColor = 1);
        int playerColor;
//        string playerName;
        virtual int decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth = 1)=0;
        virtual void gameResult(int winner);
};

#endif // PLAYER_H
