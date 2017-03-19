#include "MiniMax.h"
#include "chessState.h"
#include "move.h"
#include "Evaluator.h"
#include <climits>
#include <iostream>

#define wPawn 1
#define bPawn -1
#define wKnight 2
#define bKnight -2
#define wBishop 3 
#define bBishop -3
#define wRook 4
#define bRook -4
#define wQueen 5
#define bQueen -5
#define wKing 6
#define bKing -6

using namespace std;

Evaluator* MiniMax::evaluator = nullptr;


MiniMax::MiniMax(int depth, chessState gameState) : depth(depth), gameState(gameState)
{
	moveIndex = -1;
	if (evaluator == nullptr) {
		evaluator = new Evaluator(1, 1000, 100, 100);
	}
}

int MiniMax::moveToMake(chessMove& m) {
	Maximize(gameState, INT_MIN + 1, INT_MAX - 1, depth);
	m = bestMove;
	return moveIndex;
}

bool inCheck(chessState);

int MiniMax::Maximize(chessState gameState, int alpha, int beta, int depth) {
	if (depth == 0) {
		int value = evaluator->evaluate(&gameState);
		return value;
	}
	chessMove bestMove;
	int moveIndex = -1;
	chessMove *nextMoves;
	int count = gameState.makeValidMovesList();
	nextMoves = gameState.Moves;
	int value = INT_MIN;
	for (int i = 0; i < count; ++i) {
		chessState nextState = gameState;
		nextState.makeMove(nextMoves[i]);
		if (inCheck(nextState))
		{
			continue;													// skip if move leads into check
		}
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
	this->moveIndex = moveIndex;
	return value;
}

int MiniMax::Minimize(chessState gameState, int alpha, int beta, int depth) {
	if (depth == 0) {
		int value = evaluator->evaluate(&gameState);
		return value;
	}
	chessMove bestMove;
	int moveIndex = -1;
	chessMove *nextMoves;
	int count = gameState.makeValidMovesList();
	nextMoves = gameState.Moves;
	int value = INT_MAX;
	for (int i = 0; i < count; ++i) {
		chessState nextState = gameState;
		nextState.makeMove(nextMoves[i]);
		if (inCheck(nextState))												
		{
			continue;																// skip if move leads into check
		}
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
	this->moveIndex = moveIndex;
	return value;
}


bool inCheck(chessState state) {

	bool blocked;

	int enemyPawn;
	int enemyKnight;
	int enemyBishop;
	int enemyRook;
	int enemyQueen;
	int myKing;
	int kingI;
	int kingJ;

	if (state.playerToMove == -1) {
		// black's turn
		// whites are enemies
		enemyPawn = wPawn;
		enemyKnight = wKnight;
		enemyBishop = wBishop;
		enemyRook = wRook;
		enemyQueen = wQueen;
		myKing = bKing;
	}
	else {
		// white's turn
		// blacks are enemies
		enemyPawn = bPawn;
		enemyKnight = bKnight;
		enemyBishop = bBishop;
		enemyRook = bRook;
		enemyQueen = bQueen;
		myKing = wKing;
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (state.board[i][j] == myKing) {
				kingI = i;
				kingJ = j;
				break;
			}
		}
	}

	// For pawn
	if (state.board[kingI + 1][kingJ - 1] == enemyPawn || state.board[kingI + 1][kingJ + 1] == enemyPawn) {
		return true;
	}

	if (state.board[kingI - 1][kingJ - 2] == enemyKnight || state.board[kingI - 2][kingJ - 1] == enemyKnight || state.board[kingI - 2][kingJ + 1] == enemyKnight || state.board[kingI - 1][kingJ + 2] == enemyKnight || state.board[kingI + 1][kingJ - 2] == enemyKnight || state.board[kingI + 2][kingJ - 1] == enemyKnight || state.board[kingI + 2][kingJ + 1] == enemyKnight || state.board[kingI + 1][kingJ + 2] == enemyKnight) {
		return true;
	}


	// For Rook and Queen
	blocked = false;
	for (int i = kingI + 1; !blocked && i < 8; ++i) {
		if (state.board[i][kingJ] == enemyRook || state.board[i][kingJ] == enemyQueen) {
			return true;
		}
		else if (state.board[i][kingJ] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}

	blocked = false;

	for (int i = kingI - 1; !blocked && i >= 0; --i) {
		if (state.board[i][kingJ] == enemyRook || state.board[i][kingJ] == enemyQueen) {
			return true;
		}
		else if (state.board[i][kingJ] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}


	blocked = false;

	for (int j = kingJ - 1; !blocked && j >= 0; --j) {
		if (state.board[kingI][j] == enemyRook || state.board[kingI][j] == enemyQueen) {
			return true;
		}
		else if (state.board[kingI][j] != '.') {
			// blocked by another piece
			blocked = true;
		}
	}


	blocked = false;
	for (int j = kingJ + 1; !blocked && j < 8; ++j) {
		if (state.board[kingI][j] == enemyRook || state.board[kingI][j] == enemyQueen) {
			return true;
		}
		else if (state.board[kingI][j] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}

	// For Bishop and Queen
	blocked = false;
	for (int i = 1; !blocked && kingI + i < 8 && kingJ + i < 8; ++i) {
		if (state.board[kingI + i][kingJ + i] == enemyBishop || state.board[kingI + i][kingJ + i] == enemyQueen) {
			return true;
		}
		else if (state.board[kingI + i][kingJ + i] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}

	blocked = false;
	for (int i = 1; !blocked && kingI - i >= 0 && kingJ - i >= 0; ++i) {
		if (state.board[kingI - i][kingJ - i] == enemyBishop || state.board[kingI - i][kingJ - i] == enemyQueen) {
			return true;
		}
		else if (state.board[kingI - i][kingJ - i] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}

	blocked = false;
	int j = 1;
	for (int i = 1, j = 1; !blocked && kingI + i < 8 && kingJ - j >= 0; ++i, ++j) {
		if (state.board[kingI + i][kingJ - j] == enemyBishop || state.board[kingI + i][kingJ - j] == enemyQueen) {
			return true;
		}
		else if (state.board[kingI + i][kingJ - j] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}

	blocked = false;
	for (int i = 1, j = 1; !blocked && kingI - i >= 0 && kingJ + j < 8; ++i, ++j) {
		if (state.board[kingI - i][kingJ + i] == enemyBishop || state.board[kingI - i][kingJ + i] == enemyQueen) {
			return true;
		}
		else if (state.board[kingI - i][kingJ + i] != 0) {
			// blocked by another piece
			blocked = true;
		}
	}
	return false;
}
