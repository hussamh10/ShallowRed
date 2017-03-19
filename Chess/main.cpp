#include <iostream>
#include "groupName.h"
#include "chessState.h"
#include "move.h"
using namespace std;

ostream& operator<<(ostream& out, chessMove c) {
	out << "From (" << c.From[0] << ", " << c.From[1] << ") ";
	out << "To (" << c.To[0] << ", " << c.To[1] << ")";
	return out;
}

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
	

	bool clearscreen = false;

    cout << "Hello world!" << endl;
    chessState game;
	game.showState();
    chessMove PlayerMove;

    playerGROUP_NAME players[2]{ 1,-1 };
	int i = 0;
	
	int checkmate = 0;
	while (checkmate != -1) {
	//	_getch();
		if (clearscreen) {
			system("cls");
		}

		checkmate = players[i % 2].decideMoveUsingMINIMAX(game, PlayerMove, 3);
		cout << "Move: " << checkmate << endl;
		cout << PlayerMove << endl;
		game.makeMove(PlayerMove);
		game.showState();
		i++;
	}
	cout << "Winner: " << game.playerToMove * -1 << endl;
	cout << "Game ended in " << i << " turns" << endl;

    return 0;
}