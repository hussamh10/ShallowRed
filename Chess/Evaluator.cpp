#include "Evaluator.h"
#include <math.h>

const int VALUES [7] = {0, 100, 350, 350, 525, 1000, 4000};

Evaluator::Evaluator(int material_wt, int bonuses_wt, int mobility_wt, int penalties_wt):
material_wt(material_wt), mobility_wt(mobility_wt), bishop_pair(bishop_pair), no_pawn(no_pawn){
	state = nullptr;
}

int Evaluator::evaluate(chessState * state){
	int value = 0;
	this->state = state;
	
	value += material_wt * material();
	//value += mobility_wt * mobility();

	return value;
}

/*
	Adding piece value
	Adding bishop pair bonus
	Subtracting no-pawn penalty
*/

int Evaluator::material(){
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
				sumP1 += VALUES[p];
				if(p == 3){
					bishopP1++;
				}
				if(p == 1){
					pawnP1++;
				}
			}
			else{
				if(p == -3){
					bishopP2++;
				}
				if(p == -1){
					pawnP2++;
				}
				sumP2 += VALUES[p];
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
	TODO
		is player 1 white ?
	*/

	if(state->playerToMove == 1){
		return sumP1 - sumP2;
	}
	else{
		return sumP2 - sumP1;
	}
}


int Evaluator::mobility(){
	// TODO
	return 0;
}