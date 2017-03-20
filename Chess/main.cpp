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

	bool clearscreen = true;

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
	
	game.showState();
    chessMove PlayerMove;
	
	chessPlayer *players[2];
	players[0] = new playerGROUP_NAME(1);
	players[1] = new playerGROUP_NAME(-1);
	int i = 0;


	int checkmate = 0;
	while (checkmate != -1) {
		_getch();

		if(clearscreen) {
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


/*


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
*/