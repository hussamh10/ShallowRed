#include "Evaluator.h"
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map>
#include "MatrixSolver.h"
#include <fstream>


using namespace std;

const int VALUES [7] = {0, 100, 350, 350, 525, 1000, 0};

struct cord
{
	cord(int a, int b){
		i = a;
		j = b;
	}

	int i;
	int j;
};

/*
	Weights being used
	int:	
		pawns_p
		knight_p
		bishop_p
		rook_p
		queen_p

		pawns_o
		knight_o
		bishop_o
		rook_o
		queen_o
		
		attacking_p
		attacking_o

		no_peices_on_other_side_p
		no_peices_on_other_side_o

		mobility_p
		mobility_o

*/

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
#define ATTRIBUTES 16

Evaluator::Evaluator(int material_wt, int mobility_wt, int bishop_pair, int no_pawn):
material_wt(material_wt), mobility_wt(mobility_wt), bishop_pair(bishop_pair), no_pawn(no_pawn){
	state = nullptr;
	srand(time(NULL));
	for(int i = 0; i < ATTRIBUTES; i++){
		weights.push_back(1);
	}
}

double Evaluator::evaluate(chessState * state, int playerToMove){
	this->playerToMove = playerToMove;
	this->state = state;
	int value = 0;
	
	int p1, p2;

	value += material_wt * material();
	value += mobility_wt/10 * mobility();
	value += mobility_wt * attacking(p1, p2);
	value += 100000*regression();
	//cout << 100000*regression() << " ";

	value += rand() % 10;

	/*
		Test Code ahead

	value = 0;
	value = regression();
	value += rand() % 10;
	*/

	return value;
}

double Evaluator::regression(){
	vector<int> X = getX();
	double y = 0;

	for(int i = 0; i < X.size(); i++){
		y += X[i] * weights[i];
	}

	return y;
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

	if(playerToMove > 0){
		return sumP1 - sumP2;
	}
	else{
		return sumP2 - sumP1;
	}
}

int Evaluator::mobility(){
	return state->makeValidMovesList();
}

int Evaluator::attacking(int &p1, int &p2){
	int attackingP1 = 0;
	int attackingP2 = 0;

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int p = state->board[i][j];

			switch(p){
				case wPawn:
					attackingP1 += pawnAttacking(i, j);
					break;
				case bPawn:
					attackingP2 += pawnAttacking(i, j);
					break;

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
	if(playerToMove > 0){
		p1 = attackingP1;
		p2 = attackingP2;
		return attackingP1 - attackingP2;
	}
	else{
		p1 = attackingP2;
		p2 = attackingP1;
		return attackingP2 - attackingP1;
	}
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

	for(int i = r, j = c; i < 8 && j < 8; i++, j++){
		p = state->board[i][j];
		if(p != 0 && i != r){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r, j = c; i >= 0 && j >= 0; i--, j--){
		p = state->board[i][j];
		if(p != 0 && i != r){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r, j = c; i >= 0 && j < 8; i--, j++){
		p = state->board[i][j];
		if(p != 0 && i != r){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r, j = c; i < 8 && j >= 0; i++, j--){
		p = state->board[i][j];
		if(p != 0 && i != r){
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
		if(p != 0 && i != r){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = r; i >= 0; i--){
		p = state->board[i][c];
		if(p != 0 && i != r){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = c; i < 8; i++){
		p = state->board[r][i];
		if(p != 0 && i != c){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}

	for(int i = c; i >= 8; i--){
		p = state->board[r][i];
		if(p != 0 && i != c){
			if(!sameSign(p, x)){
				attacking++;
			}
			break;
		}
	}
	return attacking;
}

int Evaluator::pawnAttacking(int i, int j){
	int p = state->board[i][j];
	int attacking = 0;

	if(p > 0){ 
		if(i > 0){
			if(j > 0){
				int b = state->board[i - 1][j - 1];
				if(b != 0){
					if(!sameSign(p, b)){
						attacking++;
					}
				}
			}	
			if(j < 7){
				int b = state->board[i - 1][j + 1];
				if(b != 0){
					if(!sameSign(p, b)){
						attacking++;
					}
				}
			}
		}
	}

	if(p < 0){ 
		if(i < 7){
			if(j > 0)
			{
				int b = state->board[i + 1][j - 1];
				if(b != 0){
					if(!sameSign(p, b))
					{
						attacking++;
					}
				}
			}	
			if(j < 7)
			{
				int b = state->board[i + 1][j + 1];
				if(b != 0){
					if(!sameSign(p, b)){
						attacking++;
					}
				}
			}
		}
	}
	return attacking;
}

void Evaluator::peicesOnOtherSide(int &player, int &opponent){
	player = 0;
	opponent = 0;

	int white = 0;
	int black = 0;
	bool white_playing = (playerToMove > 0);
	int p;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 8; j++){
			p = state->board[i][j];
			if(p > 0){
				white++;
			}
		}
	}


	for(int i = 4; i < 8; i++){
		for(int j = 0; j < 8; j++){
			p = state->board[i][j];
			if(p < 0){
				black++;
			}
		}
	}

	if(white_playing){
		player = white;
		opponent = black;
	}
	else{
		player = black;
		opponent = white;
	}
}

void Evaluator::addToPool(chessState* r_state, int score, int playerToMove){
	state = r_state;
	state->playerToMove = playerToMove;
	this->playerToMove = playerToMove;
	pool.push_back(RegressionData(getX(), score));
}

void Evaluator::writeToFile(string filename){
	ofstream file(filename, ios::trunc);

	file << pool.size() << endl;
	file << pool[0].attribute_values.size() << endl;

	for(int i = 0; i < pool.size(); i++){
		file << pool[i].toString();
		file << endl;
	}
	file.close();
}

void Evaluator::readFromFile(string filename){
	ifstream file(filename);
	int c;
	int r;

	file >> c;
	file >> r;

	for(int i = 0; i < c; i++){
		vector<int> d;
		for(int i = 0; i < r; i++){
			int temp;
			file >> temp;
			d.push_back(temp);
		}
		int y;
		file >> y;
		pool.push_back(RegressionData(d, y));
	}
}

vector<int> Evaluator::getX(){
	std::vector<int> scores;

	map<int, int> count = getPeiceCount(state);

	for(int i = 1; i < 11; i++){
		scores.push_back(count[i]);
	}

	int attacking_p = 0;
	int attacking_o = 0;

	attacking(attacking_p, attacking_o);

	scores.push_back(attacking_p);
	scores.push_back(attacking_o);

	int no_peices_on_other_side_p = 0;
	int no_peices_on_other_side_o = 0;

	peicesOnOtherSide(no_peices_on_other_side_p, no_peices_on_other_side_o);

	scores.push_back(no_peices_on_other_side_p);
	scores.push_back(no_peices_on_other_side_o);

	int mobility_p = state->makeValidMovesList();
	playerToMove *= -1;
	int mobility_o = state->makeValidMovesList();
	playerToMove *= -1;

	scores.push_back(mobility_p);
	scores.push_back(mobility_o);

	return scores;
}

map<int, int> Evaluator::getPeiceCount(chessState* r_state){
	map<int, int> count;
	int p;
	for(int i = 0; i < 8; i++){ 
		for(int j = 0; j < 8; j++){
			p = r_state->board[i][j];
			if(p > 0){
				count[p]++;
			}
			if(p < 0){
				count[p + 5]++;
			}
		}
	}
	return count;
}

void Evaluator::computeRegressionWeights(){
	vector<vector<int>> temp_M;
	vector<int> temp_Y;

	for(RegressionData r : pool){
		temp_M.push_back(r.attribute_values);
		temp_Y.push_back(r.score);
	}

	int n, m;
	n = temp_Y.size();
	m = temp_M[0].size();

	int ** M = new int*[n];
	for(int i = 0; i < n; i++){
		M[i] = new int[m];
	}

	int * Y = new int[n];

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			M[i][j] = temp_M[i][j];
		}
	}

	for(size_t i = 0; i < n; i++){
		Y[i] = temp_Y[i];
	}

	double* W = getWeights(M, Y, n, m);

	for(int i = 0; i < m; i++){
		weights[i] = W[i];
	}
}