#include <iostream>
#include <conio.h>
#include "MatrixSolver.h"
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
	bool clearscreen = true;

    cout << "Hello world!" << endl;
    chessState game;
	game.showState();
    chessMove PlayerMove;

	playerGROUP_NAME player(1);
	playerGROUP_NAME player2(-1);
    int totalMoves = game.makeValidMovesList();

	for (int i = 0; ; ++i)
	{
		getch();
		if (clearscreen)
			system("cls");
		player.decideMoveUsingMINIMAX(game, PlayerMove, 2);
		cout << PlayerMove << endl;
		game.makeMove(PlayerMove);
		game.showState();
		getch();
		if (clearscreen)
			system("cls");
		player2.decideMoveUsingMINIMAX(game, PlayerMove, 2);
		cout << PlayerMove << endl;
		game.makeMove(PlayerMove);
		game.showState();
	}
    return 0;
}
