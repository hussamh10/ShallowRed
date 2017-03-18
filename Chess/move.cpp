#include "move.h"

chessMove::chessMove(int fromRow, int fromCol, int toRow, int toCol)
{
    //ctor
	From[0] = fromRow;
	From[1] = fromCol;
    To[0]   = toRow;
	To[1]   = toCol;
}
