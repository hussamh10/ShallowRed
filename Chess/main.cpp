#include <iostream>
#include "groupName.h"
#include "chessState.h"
#include "move.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    chessState game;
    game.showState();
    chessMove PlayerMove;

	playerGROUP_NAME player(1);
	playerGROUP_NAME player2(-1);
    int totalMoves = game.makeValidMovesList();

	for (int i = 0; i < 10; ++i)
	{

		player.decideMoveUsingMINIMAX(game, PlayerMove, 2);
		game.makeMove(PlayerMove);
		game.showState();
		player2.decideMoveUsingMINIMAX(game, PlayerMove, 2);
		game.makeMove(PlayerMove);
		game.showState();
	}
    return 0;
}
