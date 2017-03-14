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
    int totalMoves = game.makeValidMovesList();
    player.decideMoveUsingMINIMAX(game, PlayerMove, 3);
    game.makeMove(PlayerMove);
    game.showState();

    return 0;
}
