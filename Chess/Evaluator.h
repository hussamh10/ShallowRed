#pragma once
#include "chessState.h"
#include<vector>
#include <map>

using namespace std;

struct RegressionData{
	RegressionData(){}

	RegressionData(vector<int> v, int s){
		attribute_values = v;
		score = s;
	}
	vector<int> attribute_values;
	int score;
};

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
	int regression();
	
	int knightAttacking(int i, int j);
	int rookAttacking(int i, int j);
	int bishopAttacking(int i, int j);
	int queenAttacking(int i, int j);
	int pawnAttacking(int i, int j);

	void computeRegrssionWieghts();

	vector<int> getX();
	void addToPool(chessState* r_state, int score);
	map<int, int> getPeiceCount(chessState* r_state);
	void peicesOnOtherSide(int &player, int &opponent);

private:

	int material_wt;
	int mobility_wt;
	int bishop_pair;
	int no_pawn;

	vector<int> weights;
	vector<RegressionData> pool;

	chessState * state;
};