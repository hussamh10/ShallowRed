#include <iostream>
#include <conio.h>
#include "Erwin.h"
#include "chessState.h"
#include "move.h"
#include "human.h"
using namespace std;

#include"Evaluator.h"

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

bool gameInDraw(int board[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != 0 && board[i][j] != -6 && board[i][j] != 6)
			{
				return false;				// other pieces on board
			}
		}
	}
	return true;			// only Kings left
}

void promotePawn(int board[8][8])
{
	int promoteTo;
	for (int i = 0; i < 8; i++)
	{
		if (board[0][i] == wPawn)
		{
			promoteTo = rand() % 10;

			switch (promoteTo)
			{
				case 0:
				case 1:
				case 2:
				case 4:
					board[0][i] = wQueen;
					break;
				case 5:
				case 6:
					board[0][i] = wRook;
					break;
				case 7:
				case 8:
					board[0][i] = wBishop;
					break;
				case 9:
					board[0][i] = wKnight;
					break;
			}
		}
		if (board[7][i] == bPawn)
		{
			promoteTo = rand() % 10;

			switch (promoteTo)
			{
				case 0:
				case 1:
				case 2:
				case 4:
					board[7][i] = bQueen;
					break;
				case 5:
				case 6:
					board[7][i] = bRook;
					break;
				case 7:
				case 8:
					board[7][i] = bBishop;
					break;
				case 9:
					board[7][i] = bKnight;
					break;
			}
		}
	}
}

int main()
{
	bool clearscreen = true;

	cout << "Hello world!" << endl;
	chessState game;


	chessMove PlayerMove;

	chessPlayer *players[2];
	players[0] = new Erwin(1);
	players[1] = new Erwin(-1);
	int i = 0;

	int checkmate = 0;
	game.showState();
	while (checkmate != -1 && checkmate != -2) {
		_getch();
		if (clearscreen) {
			system("cls");
		}
		checkmate = players[i % 2]->decideMoveUsingMINIMAX(game, PlayerMove, 2);
		if (checkmate != -1) {
			game.makeMove(PlayerMove);
			if (gameInDraw(game.board))
			{
				checkmate = -2;		// draw
			}
			else
			{
				promotePawn(game.board);
			}
			game.showState();
		}
		i++;
	}
	if (checkmate == -1)
	{
		cout << "Winner: " << game.playerToMove*-1 << endl;
		cout << "Game ended in " << i << " turns" << endl;

		if (game.playerToMove*-1 == -1) {
			players[0]->gameResult(-1);
			players[1]->gameResult(1);
		}
		else {
			players[0]->gameResult(1);
			players[1]->gameResult(-1);
		}
	}
	else if (checkmate == -2)
	{
		cout << "Game Draw" << endl;
		cout << "Game ended in " << i << " turns" << endl;
	}
	
	

	return 0;
}