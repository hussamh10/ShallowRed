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
 //   int totalMoves = gameState.makeValidMovesList();
	int selectedMove;
    returnMove.From[0]=returnMove.From[1]=0;
    returnMove.To[0] = returnMove.To[0] = 0;
   /* if(totalMoves <= 0)
    {
		return -1;
    }*/

	MiniMax mm(depth, gameState);
	selectedMove = mm.moveToMake(returnMove);
	
	
	// push state to states taken
	chessState nextState = gameState;
	nextState.makeMove(returnMove);
	states.push_back(nextState);
	
    return selectedMove;
}


void playerGROUP_NAME::gameResult(int winner)
{
	// iterate through the state list
	for (std::list<chessState>::iterator i = states.begin(); i != states.end(); ++i){

	}
    // This function will be called by the main once the game is over
    // The integer argument winner will be either -1 or 1 depending upon
    // the player who wins the game.
    // You might use this function to call your functions to learning/enhance
    // your evaluation function.
}
