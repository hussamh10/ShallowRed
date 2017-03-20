#include <iostream>
#include <conio.h>
#include "groupName.h"
#include "chessState.h"
#include "move.h"
#include "human.h"
using namespace std;

ostream& operator<<(ostream& out, chessMove c) {
	out << "From (" << c.From[0] << ", " << c.From[1] << ") ";
	out << "To (" << c.To[0] << ", " << c.To[1] << ")";
	return out;
}

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
int main()
{

	//cout << "Hello world!" << endl;
	//chessState game;
	//game.showState();
	//chessMove PlayerMove;

	//playerGROUP_NAME player(1);
	//int totalMoves = game.makeValidMovesList();
	//// returns -1 when no more moves or checkmate
	//player.decideMoveUsingMINIMAX(game, PlayerMove, 3);
	//game.makeMove(PlayerMove);
	//game.showState();

	//return 0;
	//
	/*

	chessState a;

	for(int i = 0; i < 8; i++){
	for(int j = 0; j < 8; j++){
	//a.board[i][j] = 0;
	}
	}

	//a.board[
	a.showState();

	a.playerToMove = 1;
	Evaluator e (0, 10, 0, 0);

	cout << e.evaluate(&a);

	return 0;
	*/

	bool clearscreen = false;

	cout << "Hello world!" << endl;
	chessState game;

	/*//test
	for(int i = 0; i < 8; i++){
	for(int j = 0; j < 8; j++){
	game.board[i][j] = 0;
	}
	}

	//game.board[0][0] = -5;
	//game.board[0][5] = 5;
	game.board[5][5] = 5;


	//game.board[1][7] = -6;
	game.board[7][5] = -6;


	//Evaluator e (1, 0, 0, 0);

	//cout << e.evaluate(&game) << endl;

	//game.board[0][0] = 0;

	//cout << e.evaluate(&game) <<  endl;

	game.playerToMove = -1;

	*///test

	chessMove PlayerMove;

	chessPlayer *players[2];
	players[0] = new playerGROUP_NAME(1);
	players[1] = new playerGROUP_NAME(-1);
	int i = 0;

	/*for (int i = 0; i < 8; ++i) {

		for (int j = 0; j < 8; ++j) {
			game.board[i][j] = 0;
		}
	}
	game.board[0][0] = bRook;
	game.board[0][1] = bKnight;
	game.board[0][2] = bBishop;
	game.board[0][3] = bKing;
	game.board[0][5] = wQueen;
	game.board[1][0] = bPawn;
	game.board[1][1] = bPawn;
	game.board[1][3] = bPawn;
	game.board[1][7] = wRook;
	game.board[2][2] = bPawn;
	game.board[2][4] = bPawn;
	game.board[5][7] = wKnight;
	game.board[6][0] = wPawn;
	game.board[6][1] = wPawn;
	game.board[6][3] = wPawn;
	game.board[6][6] = wPawn;
	game.board[6][7] = wPawn;
	game.board[7][0] = wRook;
	game.board[7][1] = wKnight;
	game.board[7][2] = bQueen;
	game.board[7][4] = wKing;
	game.playerToMove = -1;
*/
	int checkmate = 0;
	game.showState();
	while (checkmate != -1) {
		_getch();

		if (clearscreen) {
			system("cls");
		}
		checkmate = players[i % 2]->decideMoveUsingMINIMAX(game, PlayerMove, 2);
		if (checkmate != -1) {
			cout << PlayerMove << endl;
			cout << "Turn: " << i << endl;
			game.makeMove(PlayerMove);
			game.showState();
		}
		i++;
	}
	cout << "Winner: " << game.playerToMove*-1 << endl;
	cout << "Game ended in " << i << " turns" << endl;

	return 0;
}