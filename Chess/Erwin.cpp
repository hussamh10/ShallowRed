#include "Erwin.h"
#include "player.h"
#include "chessState.h"
#include "MiniMax.h"
#include "Evaluator.h"

Erwin::Erwin(int playerColor):chessPlayer(playerColor)
{
    //ctor
//    this->playerName = "Group Name";

}

int Erwin::decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth){
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


void Erwin::gameResult(int winner)
{
	// iterate through the state list
	Evaluator *e = MiniMax::evaluator;
	e->readFromFile("data.txt");
	for (std::list<chessState>::iterator i = states.begin(); i != states.end(); ++i){
		// i should be the state
		e->addToPool(&(*i), winner, playerColor);
	}
	e->writeToFile("data.txt");
    // This function will be called by the main once the game is over
    // The integer argument winner will be either -1 or 1 depending upon
    // the player who wins the game.
    // You might use this function to call your functions to learning/enhance
    // your evaluation function.
}
