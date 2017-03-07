#ifndef GROUPNAME_H
#define GROUPNAME_H

#include "player.h"


class playerGROUP_NAME : public chessPlayer
{
    public:
        playerGROUP_NAME(int playerColor);
        int decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth=1);
    protected:

    private:
};

#endif // GROUPNAME_H
