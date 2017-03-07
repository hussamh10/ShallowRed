#include "groupName.h"
#include "player.h"
#include "chessState.h"

playerGROUP_NAME::playerGROUP_NAME(int playerColor):chessPlayer(playerColor)
{
    //ctor
//    this->playerName = "Group Name";

}

int playerGROUP_NAME::decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth){
    int totalMoves = gameState.makeValidMovesList();

    returnMove.From[0]=returnMove.From[1]=0;
    returnMove.To[0] = returnMove.To[0] = 0;
    if(totalMoves <=0 )
    {
        return -1;
    }


    int selectedMove = totalMoves -1;

    // Your code goes here

    returnMove.From[0] = gameState.Moves[selectedMove].From[0];
    returnMove.From[1] = gameState.Moves[selectedMove].From[1];
    returnMove.To[0] = gameState.Moves[selectedMove].To[0];
    returnMove.To[1] = gameState.Moves[selectedMove].To[1];

    return selectedMove;
}
