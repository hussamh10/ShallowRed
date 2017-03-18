#include "MiniMax.h"
#include "chessState.h"
#include "move.h"
#include "Evaluator.h"
#include <climits>
#include <iostream>
using namespace std;

Evaluator* MiniMax::evaluator = nullptr;


MiniMax::MiniMax(int depth, chessState gameState) : depth(depth), gameState(gameState)
{
	if (evaluator == nullptr) {
		evaluator = new Evaluator(1, 1000, 100, 100);
	}
}

int MiniMax::moveToMake(chessMove& m) {
	Maximize(gameState, INT_MIN + 1, INT_MAX - 1, depth);
	m = bestMove;
	return moveIndex;
}


int MiniMax::Maximize(chessState gameState, int alpha, int beta, int depth) {
	if (depth == 0) {
		int value = evaluator->evaluate(&gameState);
		return value;
	}
	chessMove bestMove;
	chessMove *nextMoves;
	int count = gameState.makeValidMovesList();
	nextMoves = gameState.Moves;
	int value = INT_MIN;
	for (int i = 0; i < count; ++i) {
		chessState nextState = gameState;
		nextState.makeMove(nextMoves[i]);
		int minimumValue = Minimize(nextState, alpha, beta, depth - 1);
		if (value < minimumValue) {
			value = minimumValue;
			bestMove = nextMoves[i];
			moveIndex = i;
		}
		alpha = alpha > value ? alpha : value;
		if (beta <= alpha) {
			// beta cut
			break;
		}
	}
	this->bestMove = bestMove;
	return value;
}

int MiniMax::Minimize(chessState gameState, int alpha, int beta, int depth) {
	if (depth == 0) {
		int value = evaluator->evaluate(&gameState);
		//cout << value << endl;
		return value;
	}
	chessMove bestMove;
	chessMove *nextMoves;
	int count = gameState.makeValidMovesList();
	nextMoves = gameState.Moves;
	int value = INT_MAX;
	for (int i = 0; i < count; ++i) {
		chessState nextState = gameState;
		nextState.makeMove(nextMoves[i]);
		int maximumValue = Maximize(nextState, alpha, beta, depth - 1);
		if (value > maximumValue) {
			value = maximumValue;
			bestMove = nextMoves[i];
			moveIndex = i;
		}
		beta = beta < value ? beta : value;
		if (beta <= alpha) {
			// alpha cut
			break;
		}
	}
	this->bestMove = bestMove;
	return value;
}