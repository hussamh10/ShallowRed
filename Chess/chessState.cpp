#include "chessState.h"
#include <iostream>
using namespace std;

bool chessState::makeMove(chessMove pieceMove)
{
    this->playerToMove *=-1;
    return true;
}

int chessState::makeValidMovesList()
{
    // This function must create a list of all valid moves for the player in the current
    // state of the game;
    //  it must return an integer specifying total valid moves in the list
    return 0;
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
