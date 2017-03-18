#pragma once
#include "chessState.h"

class Evaluator{
public:

	Evaluator(int material_wt,  int mobility_wt, int bishop_pair, int no_pawn);
	int evaluate(chessState * state);

private:

	//int bonuses();
	//int penalties();

	int material();
	int mobility();
	int attacking();
	
	int knightAttacking(int i, int j);
	int rookAttacking(int i, int j);
	int bishopAttacking(int i, int j);
	int queenAttacking(int i, int j);
	int pawnAttacking(int i, int j);


private:

	int material_wt;
	int mobility_wt;
	int bishop_pair;
	int no_pawn;

	chessState * state;
};