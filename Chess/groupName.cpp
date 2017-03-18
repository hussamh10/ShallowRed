#include "groupName.h"
#include "player.h"
#include "chessState.h"
#include "MiniMax.h"

playerGROUP_NAME::playerGROUP_NAME(int playerColor):chessPlayer(playerColor)
{
    //ctor
//    this->playerName = "Group Name";

}

int playerGROUP_NAME::decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth){
    int totalMoves = gameState.makeValidMovesList();

    returnMove.From[0]=returnMove.From[1]=0;
    returnMove.To[0] = returnMove.To[0] = 0;
    if(totalMoves <= 0)
    {
		return -1;
    }


    int selectedMove = totalMoves -1;

	MiniMax mm(depth, gameState);
	selectedMove = mm.moveToMake(returnMove);

    return selectedMove;
}
