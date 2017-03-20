#pragma once
#include "chessState.h"
#include<vector>
#include <map>
#include <string>

using namespace std;

struct RegressionData{
	RegressionData(){}

	RegressionData(vector<int> v, int s){
		attribute_values = v;
		score = s;
	}

	string to_string(){
		string a = "";
		for(int i = 0; i < attribute_values.size(); i++){
			a += std::to_string(attribute_values[i]);
			a += " ";
		}
		a += score;
		return a;
	}

	vector<int> attribute_values;
	int score;
};

class Evaluator{
public:

	Evaluator(int material_wt,  int mobility_wt, int bishop_pair, int no_pawn);
	double evaluate(chessState * state, int playerToMove);
	void addToPool(chessState* r_state, int score, int playerToMove);
	void writeToFile(string filename);
	void readFromFile(string filename);
	void computeRegressionWeights();

private:

	//int bonuses();
	//int penalties();

	int material();
	int mobility();
	int attacking(int &p1, int &p2);
	double regression();
	
	int knightAttacking(int i, int j);
	int rookAttacking(int i, int j);
	int bishopAttacking(int i, int j);
	int queenAttacking(int i, int j);
	int pawnAttacking(int i, int j);


	vector<int> getX();
	map<int, int> getPeiceCount(chessState* r_state);
	void peicesOnOtherSide(int &player, int &opponent);

private:

	int material_wt;
	int mobility_wt;
	int bishop_pair;
	int no_pawn;
	int playerToMove;

	vector<double> weights;
	vector<RegressionData> pool;

	chessState * state;
};