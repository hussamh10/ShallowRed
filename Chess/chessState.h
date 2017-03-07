#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include "move.h"

class chessState
{
    public:
        chessState();
        chessMove Moves[200];
        int makeValidMovesList();
        int playerToMove;
        int board[8][8];

        void showState();
        bool makeMove(chessMove pieceMove);


    private:
        void showPiece(int pieceCode);

};

#endif // CHESSSTATE_H
