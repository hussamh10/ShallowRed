#include <iostream>
#include <conio.h>
#include "groupName.h"
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
int main()
{
	bool clearscreen = true;

	cout << "Hello world!" << endl;
	chessState game;


	chessMove PlayerMove;

	chessPlayer *players[2];
	players[0] = new playerGROUP_NAME(1);
	players[1] = new playerGROUP_NAME(-1);
	int i = 0;

	int checkmate = 0;
	game.showState();
	while (checkmate != -1) {
		_getch();
		if (clearscreen) {
			system("cls");
		}
		checkmate = players[i % 2]->decideMoveUsingMINIMAX(game, PlayerMove, 2);
		if (checkmate != -1) {
			game.makeMove(PlayerMove);
			game.showState();
		}
		i++;
	}
	cout << "Winner: " << game.playerToMove*-1 << endl;
	cout << "Game ended in " << i << " turns" << endl;

	if(game.playerToMove*-1 == -1){
		players[0]->gameResult(-1);
		players[1]->gameResult(1);
	}
	else{
		players[0]->gameResult(1);
		players[1]->gameResult(-1);
	}

	return 0;
}