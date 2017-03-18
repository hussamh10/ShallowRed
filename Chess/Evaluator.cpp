#include "Evaluator.h"
#include <math.h>
#include <vector>

using namespace std;

const int VALUES [7] = {0, 100, 350, 350, 525, 1000, 4000};

struct cord
{
	cord(int a, int b){
		i = a;
		j = b;
	}

	int i;
	int j;
};

#define Empty 0
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

Evaluator::Evaluator(int material_wt, int bonuses_wt, int mobility_wt, int penalties_wt):
material_wt(material_wt), mobility_wt(mobility_wt), bishop_pair(bishop_pair), no_pawn(no_pawn){
	state = nullptr;
}

int Evaluator::evaluate(chessState * state){
	int value = 0;
	this->state = state;
	
	value += material_wt * material();
	//value += mobility_wt * mobility();
	value += mobility_wt * attacking();

	return value;
}

int Evaluator::material(){
/*
	Adding piece value
	Adding bishop pair bonus
	Subtracting no-pawn penalty
*/
	int sumP1 = 0;
	int sumP2 = 0;

	int bishopP1 = 0;
	int bishopP2 = 0;

	int pawnP1 = 0;
	int pawnP2 = 0;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int p = state->board[i][j];
			if(p > 0){
				sumP1 += VALUES[abs(p)];
				if(p == wBishop){
					bishopP1++;
				}
				if(p == wPawn){
					pawnP1++;
				}
			}
			else if(p < 0){
				sumP2 += VALUES[abs(p)];
				if(p == bBishop){
					bishopP2++;
				}
				if(p == bPawn){
					pawnP2++;
				}
			}
		}
	}

	if(bishopP1 == 2){
		sumP1 += bishop_pair;
	}
	if(bishopP2 == 2){
		sumP2 += bishop_pair;
	}

	if(pawnP1 < 1){
		sumP1 -= no_pawn;
	}
	if(pawnP2 < 1){
		sumP2 -= no_pawn;
	}

	/*
		white(player1) is positive
	*/

	if(state->playerToMove > 0){
		return sumP1 - sumP2;
	}
	else{
		return sumP2 - sumP1;
	}
}

int Evaluator::mobility(){
	int moves = 0;
	//moves = AllValidMoves(p1) - AllValidMoves(p2);
	return moves;
}

int Evaluator::attacking(){
	int attackingP1 = 0;
	int attackingP2 = 0;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int p = state->board[i][j];

			switch(p){
				case wKnight:
					attackingP1 += knightAttacking(i, j);
					break;
				case bKnight:
					attackingP2 += knightAttacking(i, j);
					break;

				case wBishop:
					attackingP1 += bishopAttacking(i, j);
					break;
				case bBishop:
					attackingP2 += bishopAttacking(i, j);
					break;

				case wRook:
					attackingP1 += rookAttacking(i, j);
					break;
				case bRook:
					attackingP2 += rookAttacking(i, j);
					break;

				case wQueen:
					attackingP1 += queenAttacking(i, j);
					break;
				case bQueen:
					attackingP2 += queenAttacking(i, j);
					break;

				default:
					break;
			}
		}
	}
	return attackingP1 - attackingP2;
}

int Evaluator::knightAttacking(int i, int j){
	/*
	TODO
	*/
	return 0;
}

bool sameSign(int a, int b){
	a = a / abs(a);
	b = b / abs(b);
	return (a == b);
}

int Evaluator::queenAttacking(int r, int c){
	return bishopAttacking(r, c) + rookAttacking(r, c);
}

int Evaluator::bishopAttacking(int r, int c){
	int x = state->board[r][c];
	int attacking = 0;

	int p;

	for(int i = r, j = c; i < 8, j < 8; i++, j++){
		p = state->board[i][j];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r, j = c; i >= 0, j < 8; i--, j++){
		p = state->board[i][j];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r, j = c; i > 8, j >= 0; i++, j--){
		p = state->board[i][j];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}
	return attacking;
}

int Evaluator::rookAttacking(int r, int c){
	int x = state->board[r][c];
	int attacking = 0;

	int p;

	for(int i = r; i < 8; i++){
		p = state->board[i][c];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r; i >= 0; i--){
		p = state->board[i][c];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = c; i < 8; i++){
		p = state->board[r][i];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = c; i >= 8; i--){
		p = state->board[r][i];
		if(p != 0){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	return attacking;
}
