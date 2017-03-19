#pragma once
#include "chessState.h"
#include<vector>
#include <map>

using namespace std;

class Evaluator{
public:

	Evaluator(int material_wt,  int mobility_wt, int bishop_pair, int no_pawn);
	int evaluate(chessState * state);

private:

	//int bonuses();
	//int penalties();

	int material();
	int mobility();
	int attacking(int &p1, int &p2);
	
	int knightAttacking(int i, int j);
	int rookAttacking(int i, int j);
	int bishopAttacking(int i, int j);
	int queenAttacking(int i, int j);
	int pawnAttacking(int i, int j);

	void saveScores(chessState* r_state);
	map<int, int> getPeiceCount(chessState* r_state);
	void peicesOnOtherSide(int &player, int &opponent);

private:

	int material_wt;
	int mobility_wt;
	int bishop_pair;
	int no_pawn;

	int* weights;

	vector<vector<int>> regression_scores;

	chessState * state;
};