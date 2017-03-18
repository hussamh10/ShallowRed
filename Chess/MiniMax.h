#pragma once

#include "chessState.h"

class chessMove;
class Evaluator;

class MiniMax {
public:
	MiniMax(int depth, chessState gameState);
	int moveToMake(chessMove &m);
private:
	int depth;
	chessMove bestMove;
	chessState gameState;
	int moveIndex;
	static Evaluator *evaluator;
	int Maximize(chessState gameState, int alpha, int beta, int depth);
	int Minimize(chessState gameState, int alpha, int beta, int depth);
};