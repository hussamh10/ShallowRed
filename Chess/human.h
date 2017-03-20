#pragma once

#include "player.h"
#include <iostream>
class human : public chessPlayer
{
public:
	human(int i) :chessPlayer(i){}
	int decideMoveUsingMINIMAX(chessState &gameState, chessMove& returnMove, unsigned int depth = 1) {
		int from1, from2;
		int to1, to2;

		std::cout << "From row : ";
		std::cin >> from1;
		std::cout << "From col : ";
		std::cin >> from2;
		std::cout << "To row : ";
		std::cin >> to1;
		std::cout << "To col : ";
		std::cin >> to2;

		returnMove.From[0] = from1;
		returnMove.From[1] = from2;
		returnMove.To[0] = to1;
		returnMove.To[1] = to2;
		return 1;
	}
};