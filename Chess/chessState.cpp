#include "chessState.h"
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

bool chessState::makeMove(chessMove pieceMove)
{
	board[pieceMove.To[0]][pieceMove.To[1]] = board[pieceMove.From[0]][pieceMove.From[1]];
	board[pieceMove.From[0]][pieceMove.From[1]] = 0;
	this->playerToMove *= -1;

    return true;
}

void resetStateBoard(chessState & state, int board[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			state.board[i][j] = board[i][j];
		}
	}
}

bool inCheck(chessState state);

void makeWhitePawnMoves(int board[8][8], int row, int col, chessState & state, chessMove Moves[200], int & index)
{
	// White Pawns move upwards

	if (row == 6)
	{
		if (board[row - 1][col] == 0 && board[row - 2][col] == 0)			// first move for pawn
		{
			chessMove move(row, col, row - 2, col);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
	}
	if (row >= 1)
	{
		if (board[row - 1][col] == 0)										// move one up
		{
			chessMove move(row, col, row - 1, col);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		if (col >= 1 && board[row - 1][col - 1] < 0)						// capture enemy piece diagonally (left)
		{
			chessMove move(row, col, row - 1, col-1);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		if (col <= 6 && board[row - 1][col + 1] < 0)						// capture enemy piece diagonally (right)
		{
			chessMove move(row, col, row - 1, col + 1);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
	}
}

void makeBlackPawnMoves(int board[8][8], int row, int col, chessState & state, chessMove Moves[200], int & index)
{
	// Black Pawns move downwards

	if (row == 1)
	{
		if (board[row + 1][col] == 0 && board[row + 2][col] == 0)			// first move for pawn
		{
			chessMove move(row, col, row + 2, col);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
	}
	if (row <= 6)
	{
		if (board[row + 1][col] == 0)										// move one down
		{
			chessMove move(row, col, row + 1, col);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		if (col >= 1 && board[row + 1][col - 1] > 0)						// capture enemy piece diagonally (left)
		{
			chessMove move(row, col, row + 1, col - 1);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		if (col <= 6 && board[row + 1][col + 1] > 0)						// capture enemy piece diagonally (right)
		{
			chessMove move(row, col, row + 1, col + 1);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
	}
}

void TwoDownOneRight(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row + 2][col + 1] == 0 || isWhite == (board[row + 2][col + 1] < 0))			// (2-down, 1-right)
	{																						// capture if enemy
		chessMove move(row, col, row + 2, col + 1);											// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoDownOneLeft(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row + 2][col - 1] == 0 || isWhite == (board[row + 2][col - 1] < 0))			// (2-down, 1-left)
	{																						// capture if enemy
		chessMove move(row, col, row + 2, col - 1);											// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoUpOneRight(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row - 2][col + 1] == 0 || isWhite == (board[row - 2][col + 1] < 0))			// (2-up, 1-right)
	{																						// capture if enemy
		chessMove move(row, col, row - 2, col + 1);											// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoUpOneLeft(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row - 2][col - 1] == 0 || isWhite == (board[row - 2][col - 1] < 0))			// (2-up, 1-left)
	{																						// capture if enemy
		chessMove move(row, col, row - 2, col - 1);											// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoLeftOneDown(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row + 1][col - 2] == 0 || isWhite == (board[row + 1][col - 2] < 0))			// (2-left, 1-down)
	{																						// capture if enemy
		chessMove move(row, col, row + 1, col - 2);								// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoLeftOneUp(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row - 1][col - 2] == 0 || isWhite == (board[row - 1][col - 2] < 0))			// (2-left, 1-up)
	{																						// capture if enemy
		chessMove move(row, col, row - 1, col - 2);								// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoRightOneDown(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row + 1][col + 2] == 0 || isWhite == (board[row + 1][col + 2] < 0))			// (2-right, 1-down)
	{																						// capture if enemy
		chessMove move(row, col, row + 1, col + 2);								// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void TwoRightOneUp(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (board[row - 1][col + 2] == 0 || isWhite == (board[row - 1][col + 2] < 0))			// (2-right, 1-up)
	{																						// capture if enemy
		chessMove move(row, col, row - 1, col + 2);								// move if empty
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

void makeKnightMoves(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (row <= 1)																					// only possible to move down
	{
		if (col <= 1)																				
		{
			TwoDownOneRight(board, row, col, isWhite, state, Moves, index);
			TwoRightOneDown(board, row, col, isWhite, state, Moves, index);
			if (col == 1)																			
			{
				TwoDownOneLeft(board, row, col, isWhite, state, Moves, index);
			}
		}
		else if (col >= 6)																			
		{
			TwoDownOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoLeftOneDown(board, row, col, isWhite, state, Moves, index);
			if (col == 6)																			
			{
				TwoDownOneRight(board, row, col, isWhite, state, Moves, index);
			}
		}
		else																						// all moves possible except up
		{
			TwoLeftOneDown(board, row, col, isWhite, state, Moves, index);
			TwoDownOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoDownOneRight(board, row, col, isWhite, state, Moves, index);
			TwoRightOneDown(board, row, col, isWhite, state, Moves, index);
		}
	}
	else if (row >= 6)																				// only possible to move up
	{
		if (col <= 1)																				
		{
			TwoUpOneRight(board, row, col, isWhite, state, Moves, index);
			TwoRightOneUp(board, row, col, isWhite, state, Moves, index);
			if (col == 1)																			
			{
				TwoUpOneLeft(board, row, col, isWhite, state, Moves, index);
			}
		}
		else if (col >= 6)																			
		{
			TwoUpOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoLeftOneUp(board, row, col, isWhite, state, Moves, index);
			if (col == 6)																			
			{
				TwoUpOneRight(board, row, col, isWhite, state, Moves, index);
			}
		}
		else																						// all possible moves except down 
		{
			TwoLeftOneUp(board, row, col, isWhite, state, Moves, index);
			TwoUpOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoUpOneRight(board, row, col, isWhite, state, Moves, index);
			TwoRightOneUp(board, row, col, isWhite, state, Moves, index);
		}
	}
	else
	{
		if (col <= 1)
		{
			TwoUpOneRight(board, row, col, isWhite, state, Moves, index);
			TwoRightOneUp(board, row, col, isWhite, state, Moves, index);
			TwoRightOneDown(board, row, col, isWhite, state, Moves, index);
			TwoDownOneRight(board, row, col, isWhite, state, Moves, index);
			if (col == 1)
			{
				TwoUpOneLeft(board, row, col, isWhite, state, Moves, index);
				TwoDownOneLeft(board, row, col, isWhite, state, Moves, index);
			}
		}
		else if (col >= 6)
		{
			TwoUpOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoLeftOneUp(board, row, col, isWhite, state, Moves, index);
			TwoLeftOneDown(board, row, col, isWhite, state, Moves, index);
			TwoDownOneLeft(board, row, col, isWhite, state, Moves, index);
			if (col == 6)
			{
				TwoUpOneRight(board, row, col, isWhite, state, Moves, index);
				TwoDownOneRight(board, row, col, isWhite, state, Moves, index);
			}
		}
		else																						// all possible moves 
		{
			TwoLeftOneUp(board, row, col, isWhite, state, Moves, index);
			TwoUpOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoUpOneRight(board, row, col, isWhite, state, Moves, index);
			TwoRightOneUp(board, row, col, isWhite, state, Moves, index);
			TwoRightOneDown(board, row, col, isWhite, state, Moves, index);
			TwoDownOneRight(board, row, col, isWhite, state, Moves, index);
			TwoDownOneLeft(board, row, col, isWhite, state, Moves, index);
			TwoLeftOneDown(board, row, col, isWhite, state, Moves, index);
		}
	}
}

void UpLeft(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = true;
	for (int i = row - 1, j = col - 1; empty && i >= 0 && j >= 0; --i, --j)				// up-left
	{
		if (board[i][j] == 0)															// empty or enemy
		{
			chessMove move(row, col, i, j);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[i][j] < 0))
		{
			chessMove move(row, col, i, j);									// enemy
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[i][j] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}

void UpRight(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = true;
	for (int i = row - 1, j = col + 1; empty && i >= 0 && j <= 7; --i, ++j)				// up-right
	{
		if (board[i][j] == 0)															// empty or enemy
		{
			chessMove move(row, col, i, j);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[i][j] < 0))
		{
			chessMove move(row, col, i, j);									// enemy
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[i][j] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}

void DownLeft(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = true;
	for (int i = row + 1, j = col - 1; empty && i <= 7 && j >= 0; ++i, --j)				// down-left
	{
		if (board[i][j] == 0)															// empty or enemy
		{
			chessMove move(row, col, i, j);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[i][j] < 0))
		{
			chessMove move(row, col, i, j);									// enemy
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[i][j] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}

void DownRight(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = true;
	for (int i = row + 1, j = col + 1; empty && i <= 7 && j <= 7; ++i, ++j)				// down-right
	{
		if (board[i][j] == 0)															// empty or enemy
		{
			chessMove move(row, col, i, j);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[i][j] < 0))
		{
			chessMove move(row, col, i, j);									// enemy
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[i][j] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}

void makeBishopMoves(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (row == 0)
	{
		if (col == 0)
		{
			DownRight(board, row, col, isWhite, state, Moves, index);
		}
		else if (col == 7)
		{
			DownLeft(board, row, col, isWhite, state, Moves, index);
		}
		else
		{
			DownRight(board, row, col, isWhite, state, Moves, index);
			DownLeft(board, row, col, isWhite, state, Moves, index);
		}
	}
	else if (row == 7)
	{
		if (col == 0)
		{
			UpRight(board, row, col, isWhite, state, Moves, index);
		}
		else if (col == 7)
		{
			UpLeft(board, row, col, isWhite, state, Moves, index);
		}
		else
		{
			UpRight(board, row, col, isWhite, state, Moves, index);
			UpLeft(board, row, col, isWhite, state, Moves, index);
		}
	}
	else
	{
		if (col == 0)
		{
			UpRight(board, row, col, isWhite, state, Moves, index);
			DownRight(board, row, col, isWhite, state, Moves, index);
		}
		else if (col == 7)
		{
			UpLeft(board, row, col, isWhite, state, Moves, index);
			DownLeft(board, row, col, isWhite, state, Moves, index);
		}
		else
		{
			UpLeft(board, row, col, isWhite, state, Moves, index);
			UpRight(board, row, col, isWhite, state, Moves, index);
			DownRight(board, row, col, isWhite, state, Moves, index);
			DownLeft(board, row, col, isWhite, state, Moves, index);
		}
	}
	
}

void RookUp(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = true;

	for (int i = row - 1; empty && i >= 0; --i)											// up
	{
		if (board[i][col] == 0)															// empty
		{
			chessMove move(row, col, i, col);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[i][col] < 0))										// enemy
		{
			chessMove move(row, col, i, col);
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[i][col] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}


void RookDown(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = false;

	for (int i = row + 1; empty && i <= 7; ++i)											// down
	{
		if (board[i][col] == 0)															// empty 
		{
			chessMove move(row, col, i, col);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[i][col] < 0))										// enemy
		{
			chessMove move(row, col, i, col);
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[i][col] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}


void RookLeft(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = false;

	for (int j = col - 1; empty && j >= 0; --j)											// down
	{
		if (board[row][j] == 0)															// empty
		{
			chessMove move(row, col, row, j);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[row][j] < 0))										// enemy
		{
			chessMove move(row, col, row, j);
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[row][j] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}


void RookRight(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	bool empty = false;

	for (int j = col + 1; empty && j <= 7; ++j)											// down
	{
		if (board[row][j] == 0)															// empty 
		{
			chessMove move(row, col, row, j);
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (isWhite == (board[row][j] < 0))										// enemy
		{
			chessMove move(row, col, row, j);
			empty = false;
			resetStateBoard(state, board);
			state.makeMove(move);
			if (!inCheck(state))
			{
				Moves[index++] = move;
			}
		}
		else if (board[row][j] > 0 == isWhite)											// same colour piece found on diagonal
		{
			empty = false;
		}
	}
}

void makeRookMoves(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	if (row > 0)
	{
		RookUp(board, row, col, isWhite, state, Moves, index);
	}

	if (row < 7)
	{
		RookDown(board, row, col, isWhite, state, Moves, index);
	}

	if (col > 0)
	{
		RookLeft(board, row, col, isWhite, state, Moves, index);
	}

	if (col < 7)
	{
		RookRight(board, row, col, isWhite, state, Moves, index);
	}
}

void makeQueenMoves(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	makeBishopMoves(board, row, col, isWhite, state, Moves, index);
	makeRookMoves(board, row, col, isWhite, state, Moves, index);
}

void makeKingMoves(int board[8][8], int row, int col, bool isWhite, chessState & state, chessMove Moves[200], int & index)
{
	// move if empty, capture if enemy

	if (row > 0 && (board[row - 1][col] == 0 || isWhite == (board[row - 1][col] < 0)))		
	{
		chessMove move(row, col, row - 1, col);
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
	if (row < 7 && (board[row + 1][col] == 0 || isWhite == (board[row + 1][col] < 0)))		
	{
		chessMove move(row, col, row + 1, col);
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
	if (col > 0 && (board[row][col - 1] == 0 || isWhite == (board[row][col - 1] < 0)))
	{
		chessMove move(row, col, row, col - 1);
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
	if (col < 7 && (board[row][col + 1] == 0 || isWhite == (board[row][col + 1] < 0)))
	{
		chessMove move(row, col, row, col + 1);
		resetStateBoard(state, board);
		state.makeMove(move);
		if (!inCheck(state))
		{
			Moves[index++] = move;
		}
	}
}

int chessState::makeValidMovesList()
{
	int pieceCode;		// to temporarily store piece
	int index = 0;		// the index to store generated move in Moves[200], also serves as count.
	chessState nextState;
	nextState.playerToMove = this->playerToMove;
	resetStateBoard(nextState, this->board);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pieceCode = board[i][j];

			switch (playerToMove)
			{
				case 1:
					switch (pieceCode)
					{
						case 1:
							makeWhitePawnMoves(board, i, j, nextState, Moves, index);
							break;
						case 2:
							makeKnightMoves(board, i, j, pieceCode>0, nextState, Moves, index);
							break;
						case 3:
							makeBishopMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						case 4:
							makeRookMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						case 5:
							makeQueenMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						case 6:
							makeKingMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						default:
							break;
					}
					break;

				case -1:
					switch (pieceCode)
					{
						case -1:
							makeBlackPawnMoves(board, i, j, nextState, Moves, index);
							break;
						case -2:
							makeKnightMoves(board, i, j, pieceCode>0, nextState, Moves, index);
							break;
						case -3:
							makeBishopMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						case -4:
							makeRookMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						case -5:
							makeQueenMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						case -6:
							makeKingMoves(board, i, j, pieceCode > 0, nextState, Moves, index);
							break;
						default:
							break;
					}
					break;
			}
		}
	}
    // This function must create a list of all valid moves for the player in the current
    // state of the game;
    //  it must return an integer specifying total valid moves in the list
	return index;
}

void chessState::showPiece(int pieceCode)
{
    if (pieceCode < 0)
        cout<< "B";
    else if (pieceCode > 0)
        cout<<"W";
    switch (pieceCode)
    {
        case 0:
            cout<<"-";
            break;

        case 1:
        case -1:
            cout<<"P";
            break;
        case 2:
        case -2:
            cout<<"N";
            break;
        case 3:
        case -3:
            cout<<"B";
            break;
        case 4:
        case -4:
            cout<<"R";
            break;
        case 5:
        case -5:
            cout<<"Q";
            break;
        case 6:
        case -6:
            cout<<"K";
            break;
    }
    cout<<"\t";
}

void chessState::showState()
{
    cout<<endl<<"Player To Move:\t";
    if(playerToMove > 0)
        cout<<"WHITE"<<endl;
    else
        cout<<"Black"<<endl;

    cout<<endl<<endl;

    for (int i=0;  i< 8; i++)
    {
        for(int j=0; j< 8; j++)
        {
            showPiece(board[i][j]);
        }
        cout<<endl<<endl;
    }
}

chessState::chessState()
{
    //ctor

    playerToMove = 1;

    board[0][0] = -4;board[0][1] = -2;board[0][2] = -3;board[0][3] = -5;
    board[0][4] = -6;board[0][5] = -3;board[0][6] = -2;board[0][7] = -4;

    board[1][0] = -1;board[1][1] = -1;board[1][2] = -1;board[1][3] = -1;
    board[1][4] = -1;board[1][5] = -1;board[1][6] = -1;board[1][7] = -1;

    board[2][0] = 0;board[2][1] = 0;board[2][2] = 0;board[2][3] = 0;
    board[2][4] = 0;board[2][5] = 0;board[2][6] = 0;board[2][7] = 0;

    board[3][0] = 0;board[3][1] = 0;board[3][2] = 0;board[3][3] = 0;
    board[3][4] = 0;board[3][5] = 0;board[3][6] = 0;board[3][7] = 0;

    for (int i=4;  i< 8; i++)
    {
        for(int j=0; j< 8; j++)
        {
            board[i][j] = -board[7 - i][j];
        }
    }
}

bool inCheck(chessState state) {

	int playerToMove = state.playerToMove;
	bool blocked;

	int enemyPawn;
	int enemyKnight;
	int enemyBishop;
	int enemyRook;
	int enemyQueen;
	int myKing;
	int kingI;
	int kingJ;

	if (playerToMove == -1) {
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
	if (kingJ != 0 && kingJ != 7 && kingI != 7)
	{
		if (state.board[kingI + 1][kingJ - 1] == enemyPawn || state.board[kingI + 1][kingJ + 1] == enemyPawn) {
			return true;
		}
	}
	
	if (kingI >= 2 && kingI <= 5 && kingJ >= 2 && kingJ <= 5)
	{
		if (state.board[kingI - 1][kingJ - 2] == enemyKnight || state.board[kingI - 2][kingJ - 1] == enemyKnight || state.board[kingI - 2][kingJ + 1] == enemyKnight || state.board[kingI - 1][kingJ + 2] == enemyKnight || state.board[kingI + 1][kingJ - 2] == enemyKnight || state.board[kingI + 2][kingJ - 1] == enemyKnight || state.board[kingI + 2][kingJ + 1] == enemyKnight || state.board[kingI + 1][kingJ + 2] == enemyKnight) {
			return true;
		}
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